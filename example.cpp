// Except for any way in which it interferes with Cedrick Collomb's 2009
// copyright assertion in the article "Burg’s Method, Algorithm and Recursion":
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <cmath>
#include <cstdio>
#include <vector>

#include "burg.hpp"

// Example program using burgs_method modified from Collomb's sample
int main(int argc, char *argv[])
{
    typedef long double real; // Try out "double" for kicks...
    using namespace std;

    // Create data to approximate
    vector<real> original(128, 0.0);
    for (size_t i = 0; i < original.size(); i++)
    {
        original[i] =     cos(i*0.01) + 0.75*cos(i*0.03)
                    + 0.5*cos(i*0.05) + 0.25*cos(i*0.11);
    }

    // Get linear prediction coefficients for orders 1 through order
    size_t maxorder = 7;
    real mean;
    vector<real> params(maxorder*(maxorder+1)/2);
    vector<real> sigma2e(maxorder), gain(maxorder), rho(maxorder);
    burgs_method(original.begin(), original.end(), mean,
                 maxorder, params.begin(), sigma2e.begin(), gain.begin(),
                 rho.begin(), false, true);

    // Display orders, mean squared discrepancy, and model coefficients
    printf("%5s  %9s %9s %9s\n", "Order", "RMS/N", "Gain", "Coefficients");
    printf("%5s  %9s %9s %9s\n", "-----", "-----", "----", "------------");
    for (size_t p = 0, c = 0; p < maxorder; ++p) {
        printf("%5lu  %9.4Lg %9.4Lg", p, sigma2e[p], gain[p]);
        for (size_t i = 0; i < p+1; ++i) printf(" %9.4Lg", params[c++]);
        putchar('\n');
    }

    return 0;
}

