// Copyright (c) 2018 Grumpy Cat Software S.L.
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa.h>
#include <gtest/gtest.h>

TEST(FeaturesTests, AbsoluteSumOfChanges) {
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double data[] = {0, 1, 2, 3, 4, 6, 8, 10, 11, 14, 17, 20};
    af::array tss(4, 3, data);

    af::array asoc = tsa::features::absoluteSumOfChanges(tss);

    // check dimensions
    af::dim4 dims = asoc.dims();
    ASSERT_EQ(dims[0], 1);
    ASSERT_EQ(dims[1], 3);
    ASSERT_EQ(dims[2], 1);
    ASSERT_EQ(dims[3], 1);

    // check distances
    double* hostResult = asoc.host<double>();    
    ASSERT_EQ(3, hostResult[0]);
    ASSERT_EQ(6, hostResult[1]);
    ASSERT_EQ(9, hostResult[2]);
}