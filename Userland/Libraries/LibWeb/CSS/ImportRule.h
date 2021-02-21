/*
 * Copyright (c) 2021, the SerenityOS developers.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include <AK/URL.h>
#include <LibWeb/CSS/CSSRule.h>
#include <LibWeb/Loader/Resource.h>

namespace Web::CSS {

class ImportRule : public CSSRule {
    AK_MAKE_NONCOPYABLE(ImportRule);
    AK_MAKE_NONMOVABLE(ImportRule);

public:
    static NonnullRefPtr<ImportRule> create(AK::URL&& url)
    {
        return adopt(*new ImportRule(move(url)));
    }

    ~ImportRule();

    const AK::URL& url() const { return m_url; }

    bool has_import_result() const { return !m_style_sheet.is_null(); }
    RefPtr<StyleSheet>& loaded_style_sheet() { return m_style_sheet; }
    const RefPtr<StyleSheet>& loaded_style_sheet() const { return m_style_sheet; }
    void set_style_sheet(const RefPtr<StyleSheet>& style_sheet) { m_style_sheet = style_sheet; }

    virtual String class_name() const { return "Import Rule"; };
    virtual Kind kind() const { return Kind::Import; };

private:
    ImportRule(AK::URL&& url);

    AK::URL m_url;
    RefPtr<StyleSheet> m_style_sheet;
};

}
