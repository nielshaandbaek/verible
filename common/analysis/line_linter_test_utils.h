// Copyright 2017-2020 The Verible Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef VERIBLE_COMMON_ANALYSIS_LINE_LINTER_TEST_UTILS_H_
#define VERIBLE_COMMON_ANALYSIS_LINE_LINTER_TEST_UTILS_H_

#include <memory>
#include <utility>
#include <vector>

#include "absl/strings/string_view.h"
#include "common/analysis/line_lint_rule.h"
#include "common/analysis/line_linter.h"
#include "common/analysis/lint_rule_status.h"
#include "common/analysis/linter_test_utils.h"
#include "common/text/text_structure.h"

namespace verible {

template <>
class LintRunner<LineLintRule> {
 public:
  explicit LintRunner(std::unique_ptr<LineLintRule> rule) {
    linter_.AddRule(std::move(rule));
  }

  LintRuleStatus Run(const TextStructureView& text_structure,
                     absl::string_view) {
    linter_.Lint(text_structure.Lines());
    // Looking for one type of rule violation at a time.
    CHECK_EQ(linter_.ReportStatus().size(), 1);
    return linter_.ReportStatus()[0];
  }

 private:
  LineLinter linter_;
};

}  // namespace verible

#endif  // VERIBLE_COMMON_ANALYSIS_LINE_LINTER_TEST_UTILS_H_
