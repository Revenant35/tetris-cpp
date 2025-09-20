#include "FontRegistry.h"
#include "Log.h"

namespace Core {
    FontRegistry::FontRegistry(const uint8_t fontSize) {
        m_FontSize = fontSize;
    }

    void FontRegistry::Clear() {
        m_Fonts.clear();
    }

    bool FontRegistry::Register(const std::string &path, const std::string &key) {
        try {
            const auto font = std::make_shared<Font>(path, m_FontSize);
            const auto [iterator, wasInserted] = m_Fonts.emplace(key, font);
            return wasInserted;
        } catch (const std::exception &e) {
            TETRIS_ERROR("Failed to register font '{}': {}", key, e.what());
            return false;
        }
    }

    std::weak_ptr<Font> FontRegistry::Find(const std::string &key) const {
        return m_Fonts.at(key);
    }
}
