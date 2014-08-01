/**
 * This file is part of the "FnordMetric" project
 *   Copyright (c) 2011-2014 Paul Asmuth, Google Inc.
 *
 * FnordMetric is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef _FNORDMETRIC_CSVBACKEND_H
#define _FNORDMETRIC_CSVBACKEND_H
#include <memory>
#include <fnordmetric/query/backends/csv/csvtableref.h>

namespace fnordmetric {
namespace query {
class ASTNode;
namespace csv_backend {

class CSVBackend {
public:

  static std::unique_ptr<TableRef> openTable(ASTNode* import);

};

}
}
}
#endif