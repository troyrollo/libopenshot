/**
 * @file
 * @brief Unit tests for openshot::Fraction
 * @author Jonathan Thomas <jonathan@openshot.org>
 *
 * @ref License
 */

// Copyright (c) 2008-2019 OpenShot Studios, LLC
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <catch2/catch.hpp>

#include "Fraction.h"

#include <map>
#include <vector>
#include <sstream>

using namespace std;
using namespace openshot;

TEST_CASE( "Constructors", "[libopenshot][fraction]" )
{
	// Create a default fraction (should be 1/1)
	Fraction f1;

	// Check default fraction
	CHECK(f1.num == 1);
	CHECK(f1.den == 1);
	CHECK(f1.ToFloat() == Approx(1.0f).margin(0.00001));
	CHECK(f1.ToDouble() == Approx(1.0f).margin(0.00001));

	// reduce fraction
	f1.Reduce();

	// Check the reduced fraction
	CHECK(f1.num == 1);
	CHECK(f1.den == 1);
	CHECK(f1.ToFloat() == Approx(1.0f).margin(0.00001));
	CHECK(f1.ToDouble() == Approx(1.0f).margin(0.00001));
}

TEST_CASE( "Alt_Constructors", "[libopenshot][fraction]" )
{
	// Use the delegating constructor for std::pair
	std::pair<int, int> args{24, 1};
	Fraction f1(args);
	CHECK(f1.num == 24);
	CHECK(f1.den == 1);
	CHECK(f1.ToFloat() == Approx(24.0f).margin(0.00001));

	// Use the delegating constructor for std::vector
	std::vector<int> v{30000, 1001};
	Fraction f2(v);
	CHECK(f2.ToFloat() == Approx(30000.0/1001.0).margin(0.00001));

	// Use the delegating constructor for std::map<std::string, int>
	std::map<std::string, int> dict;
	dict.insert({"num", 24000});
	dict.insert({"den", 1001});
	Fraction f3(dict);
	CHECK(f3.den == 1001);
	CHECK(f3.num == 24000);
	CHECK(f3.Reciprocal().ToFloat() == Approx(1001.0/24000.0).margin(0.00001));
}

TEST_CASE( "WxH_640_480", "[libopenshot][fraction]" )
{
	// Create fraction
	Fraction f1(640, 480);

	// Check fraction
	CHECK(f1.num == 640);
	CHECK(f1.den == 480);
	CHECK(f1.ToFloat() == Approx(1.33333f).margin(0.00001));
	CHECK(f1.ToDouble() == Approx(1.33333f).margin(0.00001));

	// reduce fraction
	f1.Reduce();

	// Check the reduced fraction
	CHECK(f1.num == 4);
	CHECK(f1.den == 3);
	CHECK(f1.ToFloat() == Approx(1.33333f).margin(0.00001));
	CHECK(f1.ToDouble() == Approx(1.33333f).margin(0.00001));
}

TEST_CASE( "WxH_1280_720", "[libopenshot][fraction]" )
{
	// Create fraction
	Fraction f1(1280, 720);

	// Check fraction
	CHECK(f1.num == 1280);
	CHECK(f1.den == 720);
	CHECK(f1.ToFloat() == Approx(1.77777f).margin(0.00001));
	CHECK(f1.ToDouble() == Approx(1.77777f).margin(0.00001));

	// reduce fraction
	f1.Reduce();

	// Check the reduced fraction
	CHECK(f1.num == 16);
	CHECK(f1.den == 9);
	CHECK(f1.ToFloat() == Approx(1.77777f).margin(0.00001));
	CHECK(f1.ToDouble() == Approx(1.77777f).margin(0.00001));
}

TEST_CASE( "Reciprocal", "[libopenshot][fraction]" )
{
	// Create fraction
	Fraction f1(1280, 720);

	// Check fraction
	CHECK(f1.num == 1280);
	CHECK(f1.den == 720);
	CHECK(f1.ToFloat() == Approx(1.77777f).margin(0.00001));
	CHECK(f1.ToDouble() == Approx(1.77777f).margin(0.00001));

	// Get the reciprocal of the fraction (i.e. flip the fraction)
	Fraction f2 = f1.Reciprocal();

	// Check the reduced fraction
	CHECK(f2.num == 720);
	CHECK(f2.den == 1280);
	CHECK(f2.ToFloat() == Approx(0.5625f).margin(0.00001));
	CHECK(f2.ToDouble() == Approx(0.5625f).margin(0.00001));

	// Re-Check the original fraction (to be sure it hasn't changed)
	CHECK(f1.num == 1280);
	CHECK(f1.den == 720);
	CHECK(f1.ToFloat() == Approx(1.77777f).margin(0.00001));
	CHECK(f1.ToDouble() == Approx(1.77777f).margin(0.00001));
}

TEST_CASE( "Operator ostream", "[libopenshot][fraction]" )
{
	std::stringstream output;
	openshot::Fraction f3(30000, 1001);

	output << f3;
	CHECK(output.str() == "Fraction(30000, 1001)");
}
