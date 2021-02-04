/*
 * MRCPP, a numerical library based on multiresolution analysis and
 * the multiwavelet basis which provide low-scaling algorithms as well as
 * rigorous error control in numerical computations.
 * Copyright (C) 2020 Stig Rune Jensen, Jonas Juselius, Luca Frediani and contributors.
 *
 * This file is part of MRCPP.
 *
 * MRCPP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * MRCPP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with MRCPP.  If not, see <https://www.gnu.org/licenses/>.
 *
 * For information on the complete list of contributors to MRCPP, see:
 * <https://mrcpp.readthedocs.io/>
 */

#pragma once

#include "WaveletAdaptor.h"

namespace mrcpp {

class OperatorAdaptor final : public WaveletAdaptor<2> {
public:
    OperatorAdaptor(double pr, int ms, bool ap = false, bool alloc = true)
            : WaveletAdaptor<2>(pr, ms, ap, alloc) {}

protected:
    bool splitNode(const MWNode<2> &node) const override {
        int chkCompNorm = 0;
        for (int i = 1; i < 4; i++) {
            if (node.getComponentNorm(i) > 0.0) { chkCompNorm = 1; }
        }

        const auto &idx = node.getNodeIndex();
        int chkTransl = (idx[0] == 0 or idx[1] == 0);

        int split = 1;
        split *= chkTransl;
        split *= chkCompNorm;

        return split;
    }
};

} // namespace mrcpp
