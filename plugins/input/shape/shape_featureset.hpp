/*****************************************************************************
 *
 * This file is part of Mapnik (c++ mapping toolkit)
 *
 * Copyright (C) 2011 Artem Pavlenko
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *****************************************************************************/

#ifndef SHAPE_FEATURESET_HPP
#define SHAPE_FEATURESET_HPP

//mapnik
#include <mapnik/geom_util.hpp>
#include <mapnik/datasource.hpp>

#include "shape_io.hpp"

//boost
#include <boost/scoped_ptr.hpp>
#include <boost/utility.hpp>

using mapnik::Featureset;
using mapnik::box2d;
using mapnik::feature_ptr;
using mapnik::transcoder;
using mapnik::context_ptr;

template <typename filterT>
class shape_featureset : public Featureset
{
    filterT filter_;
    shape_io shape_;
    box2d<double> query_ext_;
    boost::scoped_ptr<transcoder> tr_;
    long file_length_;
    std::vector<int> attr_ids_;
    const int row_limit_;
    mutable int count_;
    context_ptr ctx_;

public:
    shape_featureset(filterT const& filter,
                     std::string const& shape_file,
                     std::set<std::string> const& attribute_names,
                     std::string const& encoding,
                     long file_length,
                     int row_limit);
    virtual ~shape_featureset();
    feature_ptr next();
};

#endif //SHAPE_FEATURESET_HPP
