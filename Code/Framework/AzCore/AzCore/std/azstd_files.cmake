#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

set(FILES
    algorithm.h
    allocator.cpp
    allocator.h
    allocator_ref.h
    allocator_stack.h
    allocator_stateless.cpp
    allocator_stateless.h
    allocator_static.h
    allocator_traits.h
    any.h
    base.h
    config.h
    concepts/concepts.h
    concepts/concepts_assignable.h
    concepts/concepts_constructible.h
    concepts/concepts_copyable.h
    concepts/concepts_movable.h
    createdestroy.h
    docs.h
    exceptions.h
    functional.h
    functional_basic.h
    hash.cpp
    hash.h
    hash_table.h
    iterator/common_iterator.h
    iterator/iterator_primitives.h
    iterator.h
    limits.h
    numeric.h
    math.h
    optional.h
    ranges/all_view.h
    ranges/common_view.h
    ranges/elements_view.h
    ranges/empty_view.h
    ranges/filter_view.h
    ranges/iter_move.h
    ranges/iter_swap.h
    ranges/join_view.h
    ranges/join_with_view.h
    ranges/owning_view.h
    ranges/ranges.h
    ranges/ranges_adaptor.h
    ranges/ranges_algorithm.h
    ranges/ranges_functional.h
    ranges/ranges_to.h
    ranges/ref_view.h
    ranges/reverse_view.h
    ranges/single_view.h
    ranges/subrange.h
    ranges/split_view.h
    ranges/swap.h
    ranges/transform_view.h
    ranges/zip_view.h
    ranges/zip_view.inl
    ratio.h
    reference_wrapper.h
    sort.h
    time.h
    tuple.h
    utils.h
    bind/bind.h
    bind/mem_fn.h
    chrono/chrono.h
    chrono/clocks.h
    chrono/types.h
    containers/array.h
    containers/bitset.h
    containers/compressed_pair.h
    containers/compressed_pair.inl
    containers/containers_concepts.h
    containers/deque.h
    containers/fixed_forward_list.h
    containers/fixed_list.h
    containers/fixed_unordered_map.h
    containers/fixed_unordered_set.h
    containers/fixed_vector.h
    containers/forward_list.h
    containers/intrusive_list.h
    containers/intrusive_set.h
    containers/intrusive_slist.h
    containers/list.h
    containers/map.h
    containers/node_handle.h
    containers/queue.h
    containers/rbtree.h
    containers/ring_buffer.h
    containers/set.h
    containers/span.h
    containers/span.inl
    containers/stack.h
    containers/unordered_map.h
    containers/unordered_set.h
    containers/variant.h
    containers/variant.inl
    containers/variant_impl.h
    containers/vector.h
    parallel/allocator_concurrent_static.h
    parallel/atomic.h
    parallel/binary_semaphore.h
    parallel/combinable.h
    parallel/condition_variable.h
    parallel/conditional_variable.h
    parallel/config.h
    parallel/exponential_backoff.h
    parallel/lock.h
    parallel/mutex.h
    parallel/semaphore.h
    parallel/scoped_lock.h
    parallel/shared_mutex.h
    parallel/spin_mutex.h
    parallel/thread.h
    parallel/threadbus.h
    parallel/containers/concurrent_fixed_unordered_map.h
    parallel/containers/concurrent_fixed_unordered_set.h
    parallel/containers/concurrent_unordered_map.h
    parallel/containers/concurrent_unordered_set.h
    parallel/containers/concurrent_vector.h
    parallel/containers/lock_free_intrusive_stack.h
    parallel/containers/lock_free_intrusive_stamped_stack.h
    parallel/containers/lock_free_queue.h
    parallel/containers/lock_free_stack.h
    parallel/containers/lock_free_stamped_queue.h
    parallel/containers/lock_free_stamped_stack.h
    parallel/containers/internal/concurrent_hash_table.h
    delegate/delegate.h
    delegate/delegate_bind.h
    delegate/delegate_fwd.h
    function/function_base.h
    function/function_fwd.h
    function/function_template.h
    function/identity.h
    function/invoke.h
    smart_ptr/checked_delete.h
    smart_ptr/enable_shared_from_this.h
    smart_ptr/enable_shared_from_this2.h
    smart_ptr/intrusive_refcount.h
    smart_ptr/intrusive_base.h
    smart_ptr/intrusive_ptr.h
    smart_ptr/make_shared.h
    smart_ptr/scoped_array.h
    smart_ptr/scoped_ptr.h
    smart_ptr/shared_array.h
    smart_ptr/shared_count.h
    smart_ptr/shared_ptr.h
    smart_ptr/sp_convertible.h
    smart_ptr/unique_ptr.h
    smart_ptr/weak_ptr.h
    string/alphanum.cpp
    string/alphanum.h
    string/conversions.h
    string/fixed_string.h
    string/fixed_string.inl
    string/memorytoascii.h
    string/memorytoascii.cpp
    string/regex.h
    string/regex.cpp
    string/string.cpp
    string/string.h
    string/string_view.h
    string/osstring.h
    string/tokenize.h
    string/utf8/core.h
    string/utf8/unchecked.h
    string/wildcard.h
    typetraits/add_const.h
    typetraits/add_cv.h
    typetraits/add_pointer.h
    typetraits/add_reference.h
    typetraits/add_volatile.h
    typetraits/aligned_storage.h
    typetraits/alignment_of.h
    typetraits/config.h
    typetraits/common_type.h
    typetraits/common_reference.h
    typetraits/conjunction.h
    typetraits/disjunction.h
    typetraits/extent.h
    typetraits/function_traits.h
    typetraits/has_virtual_destructor.h
    typetraits/integral_constant.h
    typetraits/intrinsics.h
    typetraits/invoke_traits.h
    typetraits/is_abstract.h
    typetraits/is_arithmetic.h
    typetraits/is_array.h
    typetraits/is_assignable.h
    typetraits/is_base_of.h
    typetraits/is_class.h
    typetraits/is_compound.h
    typetraits/is_constructible.h
    typetraits/is_const.h
    typetraits/is_convertible.h
    typetraits/is_destructible.h
    typetraits/is_empty.h
    typetraits/is_enum.h
    typetraits/is_floating_point.h
    typetraits/is_function.h
    typetraits/is_fundamental.h
    typetraits/is_integral.h
    typetraits/is_lvalue_reference.h
    typetraits/is_member_function_pointer.h
    typetraits/is_member_object_pointer.h
    typetraits/is_member_pointer.h
    typetraits/is_object.h
    typetraits/is_pod.h
    typetraits/is_pointer.h
    typetraits/is_polymorphic.h
    typetraits/is_reference.h
    typetraits/is_rvalue_reference.h
    typetraits/is_same.h
    typetraits/is_scalar.h
    typetraits/is_signed.h
    typetraits/is_swappable.h
    typetraits/is_trivial.h
    typetraits/is_trivially_copyable.h
    typetraits/is_union.h
    typetraits/is_unsigned.h
    typetraits/is_void.h
    typetraits/is_volatile.h
    typetraits/negation.h
    typetraits/rank.h
    typetraits/remove_all_extents.h
    typetraits/remove_const.h
    typetraits/remove_cv.h
    typetraits/remove_cvref.h
    typetraits/remove_extent.h
    typetraits/remove_pointer.h
    typetraits/remove_reference.h
    typetraits/remove_volatile.h
    typetraits/static_storage.h
    typetraits/typetraits.h
    typetraits/type_id.h
    typetraits/type_identity.h
    typetraits/underlying_type.h
    typetraits/decay.h
    typetraits/conditional.h
    typetraits/has_member_function.h
    typetraits/void_t.h
    typetraits/internal/type_sequence_traits.h
    typetraits/internal/is_template_copy_constructible.h
    utility/as_const.h
    utility/declval.h
    utility/move.h
)
