#include <gtest/gtest.h>

#include <liballocpp/types.hpp>
#include <liballocpp/concepts/concepts.hpp>
#include <liballocpp/plcs/null.hpp>

using namespace allocpp;
using namespace allocpp::plcs;
using namespace allocpp::concepts;

ALLOCPP_CONCEPT_ASSERT((StatelessAllocPolicy<null<byte*>>));

TEST(null_plc_test, test_null_plc)
{
    typedef null<byte*> null_plc;

    null_plc plc;

    auto alloc_req = alloc_request<byte*>::builder().set_size(42).set_alignment(8).build();
    alloc_response<byte*> alloc_rsp = plc.allocate(alloc_req);
    EXPECT_EQ(nullptr, alloc_rsp.ptr());
    EXPECT_EQ(0, alloc_rsp.size());
    EXPECT_EQ(0, alloc_rsp.alignment());
    EXPECT_TRUE(alloc_rsp.extra_empty());

    auto dealloc_req = dealloc_request<byte*>::builder().set_ptr(nullptr).build();
    auto dealloc_rsp = plc.deallocate(dealloc_req);
    EXPECT_TRUE(alloc_rsp.extra_empty());

    byte v;
    EXPECT_EQ(ownership::UNDEFINED, plc.owns(nullptr));
    EXPECT_EQ(ownership::UNDEFINED, plc.owns(&v));
}