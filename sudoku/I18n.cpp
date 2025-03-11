#include "I18n.h"

#include <cassert>

const std::map<sdk::Key, std::string> ENGLISH = {
    { sdk::Key::ASK_KEY_MAP, "Keymap mode: 1 WASD 2 VIM" },
    { sdk::Key::INPUT_ERROR, "Input error!" },
    { sdk::Key::LOAD_PROGRESS_FAIL, "Load progress failed!" },
    { sdk::Key::ASK_QUIT, "Quit game? [Y/N]" },
    { sdk::Key::ASK_SAVE, "Do you want to save the game progress? [Y/N]" },
    { sdk::Key::ASK_SAVE_PATH, "Input path of the progress file:" },
    { sdk::Key::FILE_EXIST_ERROR, "This file is already exist." },
    { sdk::Key::CONTINUE, "Continue." },
    { sdk::Key::UNDO_ERROR, "No more action to undo." },
    { sdk::Key::CONGRATULATION, "Congratulation! You Win!" },
    { sdk::Key::NOT_COMPLETED, "Sorry, not completed." },
    { sdk::Key::ASK_DIFFICULTY, "Select difficulty: 1 Easy 2 Normal 3 Hard" },
};
const std::map<sdk::Key, std::string> CHINESE = {
    { sdk::Key::ASK_KEY_MAP, "设置按键模式: 1 WASD 2 VIM" },
    { sdk::Key::INPUT_ERROR, "输入错误!" },
    { sdk::Key::LOAD_PROGRESS_FAIL, "加载存档失败!" },
    { sdk::Key::ASK_QUIT, "退出游戏? [Y/N]" },
    { sdk::Key::ASK_SAVE, "保存进度? [Y/N]" },
    { sdk::Key::ASK_SAVE_PATH, "输入存档文件路径:" },
    { sdk::Key::FILE_EXIST_ERROR, "文件已存在" },
    { sdk::Key::CONTINUE, "继续" },
    { sdk::Key::UNDO_ERROR, "没有可以撤销的动作" },
    { sdk::Key::CONGRATULATION, "恭喜! 你解开了谜题!" },
    { sdk::Key::NOT_COMPLETED, "对不起, 还未完成" },
    { sdk::Key::ASK_DIFFICULTY, "设置难度: 1简单 2普通 3困难" },
};

// Default English
sdk::I18n::I18n() :
    dict_(&ENGLISH)
{
}

sdk::I18n& sdk::I18n::Instance()
{
    static sdk::I18n i18n;
    return i18n;
}

void sdk::I18n::SetLanguage(const sdk::Language language)
{
    switch (language)
    {
    case sdk::Language::ENGLISH:
        dict_ = &ENGLISH;
        break;
    case sdk::Language::CHINESE:
        dict_ = &CHINESE;
        break;
    case sdk::Language::MAX:
    default:
        assert(false);
    }
}

std::string sdk::I18n::Get(const sdk::Key key) const
{
    assert(dict_->count(key));
    return (*dict_).at(key);
}
