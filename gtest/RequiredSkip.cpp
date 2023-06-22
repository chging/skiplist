#include "gtest/gtest.h"
#include <vector>
#include "skiplist.hpp"

using namespace SKLT;

namespace {

/*
NOTE:  these are not intended as exhaustive tests.
	 You should make your own additional tests
	 VERY IMPORTANT:  if your SkipList is not templated, or if
			it is not built as a linked structure, your score for this project
			will be zero.  Be sure your SkipList compiles and runs
	 		with non-numeric data types.


IF YOUR CODE DOES NOT PASS EVERY TEST IN THIS FILE, YOUR SCORE WILL BE A ZERO.


*/

TEST(Required, TestConstruct)
{
	SkipList<unsigned, unsigned> sl;
	EXPECT_EQ( 1, sl.numLayers());
	EXPECT_EQ( 0, sl.size() );
	EXPECT_TRUE( sl.isEmpty() );
}

TEST(Required, TestSize)
{
	SkipList<unsigned, unsigned> sl;
	EXPECT_EQ( 0, sl.size() );
	for (int i = 0; i < 10; i++) {
		sl.insert(i, i);
		EXPECT_EQ( i + 1, sl.size() );
	}
}

TEST(Required, TestEmpty)
{
	SkipList<unsigned, unsigned> sl;
	EXPECT_TRUE( sl.isEmpty() );
	sl.insert(3, 5);
	EXPECT_FALSE( sl.isEmpty() );
}

TEST(Required, TestLayers)
{
	SkipList<unsigned, unsigned> sl;
	EXPECT_EQ( 1, sl.numLayers());
	sl.insert(3, 5);
	EXPECT_EQ( 1, sl.numLayers());
}

TEST(Required, TestHeight)
{
	SkipList<unsigned, unsigned> sl;
	sl.insert(3, 5);
	EXPECT_EQ( 0, sl.height(3));
	EXPECT_EQ( -1, sl.height(5));
}

TEST(Required, TestFind)
{
	SkipList<std::string, std::string> sl;
	sl.insert("Shindler", "ICS 46");
	EXPECT_TRUE(sl.find("Shindler"));
	EXPECT_FALSE(sl.find("hindler"));

	std::string v;
	EXPECT_TRUE(sl.find("Shindler", v));
	EXPECT_EQ(std::string("ICS 46"), v);
}

TEST(Required, TestInsert)
{
	SkipList<unsigned, unsigned> sl;
	EXPECT_TRUE( sl.insert(3, 5));
	EXPECT_FALSE( sl.insert(3, 5));
}

TEST(Required, SimpleAllKeysInOrder)
{
	SkipList<unsigned, unsigned> sl;
	std::vector<unsigned> expected;
	for (unsigned i = 0; i < 10; i++)
	{
		sl.insert(i, (100 + i) );
		expected.push_back( i );
	}
	EXPECT_TRUE( expected == sl.allKeysInOrder() );
}

TEST(SampleTests, TestLargestAndSmallest)
{
	SkipList<unsigned, unsigned> sl;
	for (unsigned i = 0; i < 10; i++)
	{
		sl.insert(i, (100 + i) );
	}
	EXPECT_TRUE( sl.isSmallestKey( 0 ) and sl.isLargestKey( 9 ) );

}

TEST(Required, TestRemove)
{
	SkipList<unsigned, unsigned> sl;

	for (int i = 0; i < 10; i++) {
		sl.insert(i, i);
	}

	EXPECT_FALSE(sl.remove(10));

	for (int i = 9; i >= 0; --i) {
		EXPECT_TRUE(sl.remove(i));
		EXPECT_EQ( i , sl.size() );
	}

	EXPECT_EQ( 1, sl.numLayers());
}

}
