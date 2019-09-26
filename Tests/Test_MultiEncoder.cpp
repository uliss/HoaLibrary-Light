/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include <cfloat>
#include <cmath>

#include <Hoa.hpp>
using namespace hoa;

#define CATCH_CONFIG_PREFIX_ALL
#include "catch.hpp"

CATCH_TEST_CASE("MultiEncoder 2D", "[Encoder] [MultiEncoder] [2D]")
{
    MultiEncoder<Hoa2d, float> encoder(7, 3);
    const float epsilon = FLT_EPSILON;
    std::vector<float> inputs(5);
    std::vector<float> outputs0(15);
    std::vector<float> outputs1(15);
    std::vector<float> outputs2(15);
    std::vector<float> outputs_sum(15);

    encoder.setRadius(0, 0.);
    encoder.setAzimuth(0, 0.);
    encoder.setElevation(0, 0.);
    encoder.setMute(0, false);

    encoder.setRadius(1, 1.);
    encoder.setAzimuth(1, 1.);
    encoder.setElevation(1, 1.);
    encoder.setMute(1, true);

    encoder.setRadius(2, 2.);
    encoder.setAzimuth(2, 2.);
    encoder.setElevation(2, 2.);
    encoder.setMute(2, true);

    CATCH_CHECK(encoder.getRadius(0) == 0.);
    CATCH_CHECK(encoder.getAzimuth(0) == 0.);
    CATCH_CHECK(encoder.getElevation(0) == 0.);
    CATCH_CHECK_FALSE(encoder.getMute(0));

    CATCH_CHECK(encoder.getRadius(1) == 1.);
    CATCH_CHECK(encoder.getAzimuth(1) == 1.);
    CATCH_CHECK(encoder.getElevation(1) == 1.);
    CATCH_CHECK(encoder.getMute(1));

    CATCH_CHECK(encoder.getRadius(2) == 2.);
    CATCH_CHECK(encoder.getAzimuth(2) == 2.);
    CATCH_CHECK(encoder.getElevation(2) == 2.);
    CATCH_CHECK(encoder.getMute(2));

    encoder.setMute(0, false);
    encoder.setMute(1, true);
    encoder.setMute(2, true);
    std::fill(inputs.begin(), inputs.end(), 1);
    encoder.process(inputs.data(), outputs0.data());

    CATCH_CHECK(outputs0[0] == Approx(8));
    CATCH_CHECK(outputs0[1] == 0);
    CATCH_CHECK(outputs0[2] == 0);
    CATCH_CHECK(outputs0[3] == 0);
    CATCH_CHECK(outputs0[4] == 0);
    CATCH_CHECK(outputs0[5] == 0);
    CATCH_CHECK(outputs0[6] == 0);
    CATCH_CHECK(outputs0[8] == 0);
    CATCH_CHECK(outputs0[9] == 0);
    CATCH_CHECK(outputs0[10] == 0);
    CATCH_CHECK(outputs0[11] == 0);
    CATCH_CHECK(outputs0[12] == 0);
    CATCH_CHECK(outputs0[13] == 0);
    CATCH_CHECK(outputs0[14] == 0);

    encoder.setMute(0, true);
    encoder.setMute(1, false);
    encoder.setMute(2, true);
    encoder.process(inputs.data(), outputs1.data());

    CATCH_CHECK(outputs1[0] == Approx(1));
    CATCH_CHECK(outputs1[1] == Approx(0.84147f));
    CATCH_CHECK(outputs1[2] == Approx(0.5403f));
    CATCH_CHECK(outputs1[3] == Approx(0.9093f));
    CATCH_CHECK(outputs1[4] == Approx(-0.41615f));
    CATCH_CHECK(outputs1[5] == Approx(0.14112f));
    CATCH_CHECK(outputs1[6] == Approx(-0.98999f));
    CATCH_CHECK(outputs1[8] == Approx(-0.65364f));
    CATCH_CHECK(outputs1[9] == Approx(-0.95892f));
    CATCH_CHECK(outputs1[10] == Approx(0.28366f));
    CATCH_CHECK(outputs1[11] == Approx(-0.27942f));
    CATCH_CHECK(outputs1[12] == Approx(0.96017f));
    CATCH_CHECK(outputs1[13] == Approx(0.65699f));
    CATCH_CHECK(outputs1[14] == Approx(0.7539f));

    encoder.setMute(0, true);
    encoder.setMute(1, true);
    encoder.setMute(2, false);
    encoder.process(inputs.data(), outputs2.data());

    CATCH_CHECK(outputs2[0] == Approx(0.5));
    CATCH_CHECK(outputs2[1] == Approx(0.45465f));
    CATCH_CHECK(outputs2[2] == Approx(-0.20807f));
    CATCH_CHECK(outputs2[3] == Approx(-0.3784f));
    CATCH_CHECK(outputs2[4] == Approx(-0.32682f));
    CATCH_CHECK(outputs2[5] == Approx(-0.13971f));
    CATCH_CHECK(outputs2[6] == Approx(0.48009f));
    CATCH_CHECK(outputs2[8] == Approx(-0.07275f));
    CATCH_CHECK(outputs2[9] == Approx(-0.27201f));
    CATCH_CHECK(outputs2[10] == Approx(-0.41954f));
    CATCH_CHECK(outputs2[11] == Approx(-0.26829f));
    CATCH_CHECK(outputs2[12] == Approx(0.42193f));
    CATCH_CHECK(outputs2[13] == Approx(0.4953f));
    CATCH_CHECK(outputs2[14] == Approx(0.06837f));

    encoder.setMute(0, false);
    encoder.setMute(1, false);
    encoder.setMute(2, true);
    encoder.process(inputs.data(), outputs_sum.data());

    for (size_t i = 0; i < outputs0.size(); i++) {
        CATCH_CHECK(outputs_sum[i] == Approx(outputs0[i] + outputs1[i]));
    }

    encoder.setMute(0, false);
    encoder.setMute(1, true);
    encoder.setMute(2, false);
    encoder.process(inputs.data(), outputs_sum.data());

    for (size_t i = 0; i < outputs0.size(); i++) {
        CATCH_CHECK(outputs_sum[i] == Approx(outputs0[i] + outputs2[i]));
    }

    encoder.setMute(0, true);
    encoder.setMute(1, false);
    encoder.setMute(2, false);
    encoder.process(inputs.data(), outputs_sum.data());

    for (size_t i = 0; i < outputs0.size(); i++) {
        CATCH_CHECK(outputs_sum[i] == Approx(outputs1[i] + outputs2[i]));
    }

    encoder.setMute(0, false);
    encoder.setMute(1, false);
    encoder.setMute(2, false);
    encoder.process(inputs.data(), outputs_sum.data());

    for (size_t i = 0; i < outputs0.size(); i++) {
        CATCH_CHECK(outputs_sum[i] == Approx(outputs0[i] + outputs1[i] + outputs2[i]));
    }

    encoder.setMute(0, true);
    encoder.setMute(1, true);
    encoder.setMute(2, true);
    encoder.process(inputs.data(), outputs_sum.data());

    for (size_t i = 0; i < outputs0.size(); i++) {
        CATCH_CHECK(outputs_sum[i] == 0);
    }
}

CATCH_TEST_CASE("MultiEncoder 3D", "[Encoder] [MultiEncoder] [3D]")
{
    MultiEncoder<Hoa3d, float> encoder(7, 3);
    const float epsilon = FLT_EPSILON;
    std::vector<float> inputs(5);
    std::vector<float> outputs(64);

    encoder.setRadius(0, 0.);
    encoder.setAzimuth(0, 0.);
    encoder.setElevation(0, 0.);
    encoder.setMute(0, false);

    encoder.setRadius(1, 1.);
    encoder.setAzimuth(1, 1.);
    encoder.setElevation(1, 1.);
    encoder.setMute(1, false);

    encoder.setRadius(2, 2.);
    encoder.setAzimuth(2, 2.);
    encoder.setElevation(2, 2.);
    encoder.setMute(2, false);

    CATCH_CHECK(encoder.getRadius(0) == 0.);
    CATCH_CHECK(encoder.getAzimuth(0) == 0.);
    CATCH_CHECK(encoder.getElevation(0) == 0.);
    CATCH_CHECK_FALSE(encoder.getMute(0));

    CATCH_CHECK(encoder.getRadius(1) == 1.);
    CATCH_CHECK(encoder.getAzimuth(1) == 1.);
    CATCH_CHECK(encoder.getElevation(1) == 1.);
    CATCH_CHECK_FALSE(encoder.getMute(1));

    CATCH_CHECK(encoder.getRadius(2) == 2.);
    CATCH_CHECK(encoder.getAzimuth(2) == 2.);
    CATCH_CHECK(encoder.getElevation(2) == 2.);
    CATCH_CHECK_FALSE(encoder.getMute(2));

    encoder.process(inputs.data(), outputs.data());
}
