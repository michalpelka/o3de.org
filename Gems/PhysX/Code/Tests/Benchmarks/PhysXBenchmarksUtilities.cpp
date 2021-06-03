/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/

#include <Benchmarks/PhysXBenchmarksUtilities.h>

#include <algorithm>
#include <AzCore/std/smart_ptr/make_shared.h>
#include <AzFramework/Physics/SimulatedBodies/RigidBody.h>
#include <AzFramework/Physics/Shape.h>
#include <AzFramework/Physics/PhysicsScene.h>
#include <AzFramework/Physics/Configuration/RigidBodyConfiguration.h>

namespace PhysX::Benchmarks
{
    namespace Utils
    {
        AzPhysics::SimulatedBodyHandleList CreateRigidBodies(int numRigidBodies,
            AzPhysics::Scene* scene, bool enableCCD,
            GenerateColliderFuncPtr* genColliderFuncPtr /*= nullptr*/, GenerateSpawnPositionFuncPtr* genSpawnPosFuncPtr /*= nullptr*/,
            GenerateSpawnOrientationFuncPtr* genSpawnOriFuncPtr /*= nullptr*/, GenerateMassFuncPtr* genMassFuncPtr /*= nullptr*/,
            GenerateEntityIdFuncPtr* genEntityIdFuncPtr /*= nullptr*/
        )
        {
            AzPhysics::SimulatedBodyHandleList rigidBodies;
            rigidBodies.reserve(numRigidBodies);

            AzPhysics::RigidBodyConfiguration rigidBodyConfig;
            rigidBodyConfig.m_ccdEnabled = enableCCD;
            auto rigidBodyColliderConfig = AZStd::make_shared<Physics::ColliderConfiguration>();

            auto defaultShapeConfiguration = AZStd::make_shared<Physics::BoxShapeConfiguration>(AZ::Vector3::CreateOne());
            for (int i = 0; i < numRigidBodies; i++)
            {
                //call the optional function pointers, otherwise assign a default
                if (genEntityIdFuncPtr != nullptr)
                {
                    rigidBodyConfig.m_entityId = (*genEntityIdFuncPtr)(i);
                }
                if (genMassFuncPtr != nullptr)
                {
                    rigidBodyConfig.m_mass = (*genMassFuncPtr)(i);
                }
                if (genSpawnPosFuncPtr != nullptr)
                {
                    rigidBodyConfig.m_position = (*genSpawnPosFuncPtr)(i);
                }
                if (genSpawnOriFuncPtr != nullptr)
                {
                    rigidBodyConfig.m_orientation = (*genSpawnOriFuncPtr)(i);
                }

                AZStd::shared_ptr<Physics::ShapeConfiguration> shapeConfig = nullptr;
                if (genColliderFuncPtr != nullptr)
                {
                    shapeConfig = (*genColliderFuncPtr)(i);
                }
                if (shapeConfig == nullptr)
                {
                    shapeConfig = defaultShapeConfiguration;
                }
                rigidBodyConfig.m_colliderAndShapeData = AzPhysics::ShapeColliderPair(rigidBodyColliderConfig, shapeConfig);

                AzPhysics::SimulatedBodyHandle simBodyHandle = scene->AddSimulatedBody(&rigidBodyConfig);
                rigidBodies.push_back(simBodyHandle);
            }

            return rigidBodies;
        }

        AZStd::vector<AzPhysics::RigidBody*> GetRigidBodiesFromHandles(AzPhysics::Scene* scene, const AzPhysics::SimulatedBodyHandleList& handlesList)
        {
            AZStd::vector<AzPhysics::RigidBody*> rigidBodies;
            rigidBodies.reserve(handlesList.size());
            for (auto handle : handlesList)
            {
                rigidBodies.push_back(azdynamic_cast<AzPhysics::RigidBody*>(scene->GetSimulatedBodyFromHandle(handle)));
            }
            return rigidBodies;
        }

        PrePostSimulationEventHandler::PrePostSimulationEventHandler()
            : m_sceneStartSimHandler([this](
                [[maybe_unused]] AzPhysics::SceneHandle sceneHandle,
                [[maybe_unused]] float fixedDeltaTime)
                {
                    this->PreTick();
                })
            , m_sceneFinishSimHandler([this](
                [[maybe_unused]] AzPhysics::SceneHandle sceneHandle,
                [[maybe_unused]] float fixedDeltatime)
                {
                    this->PostTick();
                })
        {

        }

        void PrePostSimulationEventHandler::Start(AzPhysics::Scene* scene)
        {
            m_subTickTimes.clear();
            scene->RegisterSceneSimulationStartHandler(m_sceneStartSimHandler);
            scene->RegisterSceneSimulationFinishHandler(m_sceneFinishSimHandler);
        }

        void PrePostSimulationEventHandler::Stop()
        {
            m_sceneStartSimHandler.Disconnect();
            m_sceneFinishSimHandler.Disconnect();
        }

        void PrePostSimulationEventHandler::PreTick()
        {
            m_tickStart = AZStd::chrono::system_clock::now();
        }

        void PrePostSimulationEventHandler::PostTick()
        {
            auto tickElapsedMilliseconds = Types::double_milliseconds(AZStd::chrono::system_clock::now() - m_tickStart);
            m_subTickTimes.emplace_back(tickElapsedMilliseconds.count());
        }

        void ReportFramePercentileCounters(benchmark::State& state, Types::TimeList& frameTimes, Types::TimeList& subTickTimes, const AZStd::vector<double>& requestedPercentiles /*= { {0.5, 0.9, 0.99} }*/)
        {
            AZStd::vector<double> framePercentiles = GetPercentiles(requestedPercentiles, frameTimes);
            AZStd::vector<double> subTickPercentiles = GetPercentiles(requestedPercentiles, subTickTimes);

            //Report the percentiles, slowest and fastest frame of the run
            int minRange = static_cast<int>(AZStd::min(requestedPercentiles.size(), framePercentiles.size()));
            for (int i = 0; i < minRange; i++)
            {
                AZStd::string label = AZStd::string::format("Frame-P%d", static_cast<int>(requestedPercentiles[i] * 100.0));
                state.counters[label.c_str()] = framePercentiles[i];
            }
            //add fastest and slowest frame time, if it doesn't exist report -1.0 (negative time is impossible, so this denotes an error).
            std::nth_element(frameTimes.begin(), frameTimes.begin(), frameTimes.end());
            state.counters["Frame-Fastest"] = !frameTimes.empty() ? frameTimes.front() : -1.0;
            std::nth_element(frameTimes.begin(), frameTimes.begin() + (frameTimes.size() - 1), frameTimes.end());
            state.counters["Frame-Slowest"] = !frameTimes.empty() ? frameTimes.back() : -1.0;

            //Report the percentiles, slowest and fastest sub tick of the run
            if (subTickTimes.empty())
            {
                return;
            }
            minRange = static_cast<int>(AZStd::min(requestedPercentiles.size(), subTickPercentiles.size()));
            for (int i = 0; i < minRange; i++)
            {
                AZStd::string label = AZStd::string::format("SubTick-P%d", static_cast<int>(requestedPercentiles[i] * 100.0));
                state.counters[label.c_str()] = subTickPercentiles[i];
            }
            //add fastest and slowest frame time, if it doesn't exist report -1.0 (negative time is impossible, so this denotes an error).
            std::nth_element(subTickTimes.begin(), subTickTimes.begin(), subTickTimes.end());
            state.counters["SubTick-Fastest"] = !subTickTimes.empty() ? subTickTimes.front() : -1.0;
            std::nth_element(subTickTimes.begin(), subTickTimes.begin() + (subTickTimes.size()-1), subTickTimes.end());
            state.counters["SubTick-Slowest"] = !subTickTimes.empty() ? subTickTimes.back() : -1.0;
        }

        void ReportFrameStandardDeviationAndMeanCounters(benchmark::State& state, const Types::TimeList& frameTimes, const Types::TimeList& subTickTimes)
        {
            StandardDeviationAndMeanResults stdivMeanFrameTimes = GetStandardDeviationAndMean(frameTimes);
            state.counters["Frame-Mean"] = aznumeric_cast<double>(aznumeric_cast<int64_t>(stdivMeanFrameTimes.m_mean * 1000.0)) / 1000.0; //truncate to 3 decimal places
            state.counters["Frame-StDev"] = aznumeric_cast<double>(aznumeric_cast<int64_t>(stdivMeanFrameTimes.m_standardDeviation * 1000.0)) / 1000.0;
            StandardDeviationAndMeanResults stdivMeanSubTickTimes = GetStandardDeviationAndMean(subTickTimes);
            state.counters["SubTick-Mean"] = aznumeric_cast<double>(aznumeric_cast<int64_t>(stdivMeanSubTickTimes.m_mean * 1000.0)) / 1000.0;
            state.counters["SubTick-StDev"] = aznumeric_cast<double>(aznumeric_cast<int64_t>(stdivMeanSubTickTimes.m_standardDeviation * 1000.0)) / 1000.0;
        }
    } // namespace Utils
} // namespace PhysX::Benchmarks
