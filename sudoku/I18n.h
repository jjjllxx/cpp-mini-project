#pragma once

#include <cstdint>
#include <map>
#include <string>

namespace sdk
{
enum class Language : std::uint8_t
{
    ENGLISH,
    CHINESE,
    MAX,
};

enum class Key : std::uint8_t
{
    ASK_KEY_MAP,
    INPUT_ERROR,
    LOAD_PROGRESS_FAIL,
    ASK_QUIT,
    ASK_SAVE,
    ASK_SAVE_PATH,
    FILE_EXIST_ERROR,
    CONTINUE,
    UNDO_ERROR,
    CONGRATULATION,
    NOT_COMPLETED,
    ASK_DIFFICULTY,
};

class I18n
{
public:

    static I18n& Instance();
    void         SetLanguage(const sdk::Language language);
    std::string  Get(const sdk::Key key) const;

private:
    I18n();

    const std::map<sdk::Key, std::string>* dict_;
};
} // namespace sdk