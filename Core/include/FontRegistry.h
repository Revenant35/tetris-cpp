#pragma once

#include "Core.h"
#include "Font.h"

namespace Core {
    class FontRegistry {
    public:
        explicit FontRegistry(uint8_t fontSize);

        void Clear();
        bool Register(const std::string &path, const std::string &key);
        std::weak_ptr<Font> Find(const std::string &key) const;
    private:
        uint8_t m_FontSize;
        std::unordered_map<std::string, std::shared_ptr<Font>> m_Fonts;
    };
}