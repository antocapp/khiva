// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <tsa.h>

#define EPSILON 1e-8

TEST(RegressionTests, Linear) {
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double dataX[] = {0.24580423, 0.59642861, 0.35879163, 0.37891011, 0.02445137,
                      0.23830957, 0.38793433, 0.68054104, 0.83934083, 0.76073689};
    af::array x = af::array(10, dataX);

    double dataY[] = {0.2217416,  0.06344161, 0.77944375, 0.72174137, 0.19413884,
                      0.51146167, 0.06880307, 0.39414268, 0.98172767, 0.30490851};
    af::array y = af::array(10, dataY);

    af::array slope, intercept, rvalue, pvalue, stderrest;
    double slope_host, intercept_host, rvalue_host, pvalue_host, stderrest_host;

    tsa::regression::linear(x, y, slope, intercept, rvalue, pvalue, stderrest);

    slope.host(&slope_host);
    intercept.host(&intercept_host);
    rvalue.host(&rvalue_host);
    pvalue.host(&pvalue_host);
    stderrest.host(&stderrest_host);

    ASSERT_NEAR(slope_host, 0.344864266, EPSILON);
    ASSERT_NEAR(intercept_host, 0.268578232, EPSILON);
    ASSERT_NEAR(rvalue_host, 0.283552942, EPSILON);
    ASSERT_NEAR(pvalue_host, 0.427239418, EPSILON);
    ASSERT_NEAR(stderrest_host, 0.412351891, EPSILON);
}

TEST(RegressionTests, LinearSinglePrecision) {
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    float dataX[] = {0.24580423, 0.59642861, 0.35879163, 0.37891011, 0.02445137,
                     0.23830957, 0.38793433, 0.68054104, 0.83934083, 0.76073689};
    af::array x = af::array(10, dataX);

    float dataY[] = {0.2217416,  0.06344161, 0.77944375, 0.72174137, 0.19413884,
                     0.51146167, 0.06880307, 0.39414268, 0.98172767, 0.30490851};
    af::array y = af::array(10, dataY);

    af::array slope, intercept, rvalue, pvalue, stderrest;
    float slope_host, intercept_host, rvalue_host, pvalue_host, stderrest_host;

    tsa::regression::linear(x, y, slope, intercept, rvalue, pvalue, stderrest);

    slope.host(&slope_host);
    intercept.host(&intercept_host);
    rvalue.host(&rvalue_host);
    pvalue.host(&pvalue_host);
    stderrest.host(&stderrest_host);

    ASSERT_NEAR(slope_host, 0.344864266, 1e-6);
    ASSERT_NEAR(intercept_host, 0.268578232, 1e-6);
    ASSERT_NEAR(rvalue_host, 0.283552942, 1e-6);
    ASSERT_NEAR(pvalue_host, 0.427239418, 1e-6);
    ASSERT_NEAR(stderrest_host, 0.412351891, 1e-6);
}

TEST(RegressionTests, LinearMultipleTimeSeries) {
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double dataX[] = {0.24580423, 0.59642861, 0.35879163, 0.37891011, 0.02445137,
                      0.23830957, 0.38793433, 0.68054104, 0.83934083, 0.76073689};
    af::array x = af::array(10, dataX);
    af::array xss = af::tile(x, 1, 2);

    double dataY[] = {0.2217416,  0.06344161, 0.77944375, 0.72174137, 0.19413884,
                      0.51146167, 0.06880307, 0.39414268, 0.98172767, 0.30490851};
    af::array y = af::array(10, dataY);
    af::array yss = af::tile(y, 1, 2);

    af::array slope, intercept, rvalue, pvalue, stderrest;

    tsa::regression::linear(xss, yss, slope, intercept, rvalue, pvalue, stderrest);

    double *slope_host = slope.host<double>();
    double *intercept_host = intercept.host<double>();
    double *rvalue_host = rvalue.host<double>();
    double *pvalue_host = pvalue.host<double>();
    double *stderrest_host = stderrest.host<double>();

    ASSERT_NEAR(slope_host[0], 0.344864266, EPSILON);
    ASSERT_NEAR(slope_host[1], 0.344864266, EPSILON);
    ASSERT_NEAR(intercept_host[0], 0.268578232, EPSILON);
    ASSERT_NEAR(intercept_host[1], 0.268578232, EPSILON);
    ASSERT_NEAR(rvalue_host[0], 0.283552942, EPSILON);
    ASSERT_NEAR(rvalue_host[1], 0.283552942, EPSILON);
    ASSERT_NEAR(pvalue_host[0], 0.427239418, EPSILON);
    ASSERT_NEAR(pvalue_host[1], 0.427239418, EPSILON);
    ASSERT_NEAR(stderrest_host[0], 0.412351891, EPSILON);
    ASSERT_NEAR(stderrest_host[1], 0.412351891, EPSILON);
}