/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */


#include <SceneAPI/FbxSceneBuilder/ImportContexts/AssImpImportContexts.h>
#include <SceneAPI/SceneCore/Components/LoadingComponent.h>

namespace AZ
{
    namespace SceneAPI
    {
        namespace FbxSceneBuilder
        {
            class AssImpTangentStreamImporter : public SceneCore::LoadingComponent
            {
            public:
                AZ_COMPONENT(AssImpTangentStreamImporter, "{AB2D1D1E-5A19-40AF-B4F4-C652DD578F43}", SceneCore::LoadingComponent);

                AssImpTangentStreamImporter();
                ~AssImpTangentStreamImporter() override = default;

                static void Reflect(ReflectContext* context);

                Events::ProcessingResult ImportTangentStreams(AssImpSceneNodeAppendedContext& context);

            protected:
                static const char* m_defaultNodeName;
            };
        } // namespace FbxSceneBuilder
    } // namespace SceneAPI
} // namespace AZ
