#include "JSONObject"
#include <cstring>

#define SPELLER_VERSION "1.0.0"
#define PROGRAM_NAME "CASIO_SPELLER_FOR_FX580VNX"

JSONObject lang_pack_obj;
std::map<std::string, std::string> opts = {};

std::string GetStringByLangPack(const std::string& index){
    return ConvertVariantToString(lang_pack_obj.map[index]);
}

void HelpScreen() noexcept {
    // English
    std::cout << "English:\n Directly Usage (using flags): spell.exe [FLAGS] [ARGUMENT] -c <context>\n";
    std::cout << " Flags         Argument(s)       Meaning\n";
    // --debug
    std::cout << " --debug       true              See what it is doing and how it processes\n";
    std::cout << "               false             Hide logs while running\n";
    // --help
    std::cout << " --help        <none>            Show this message and exit\n";
    // --version
    std::cout << " --version     <none>            See its version and exit\n";
    // -c or -context
    std::cout << " -c            <context>         The content you want to display as a tutorial on your Casio fx580vnx\n";
    std::cout << " -context      <context>         Another way to specify the context (same as '-c')\n";
    // -lang
    std::cout << " -lang         <language>        Choose a language. Supported languages by the developer are: English and Vietnamese\n"
              << "                                 Language will load as JSON Object in file <language>.json\n";
    // -p
    std::cout << " -p            Left              Your context will be on the left side of the Casio's screen\n"
              << "               Middle            Your context will be on the middle side of the Casio's screen\n"
              << "               Right             Your context will be on the right side of the Casio's screen\n";
    // Warnings
    std::cout << " Warnings:\n  + All flags can only be set once. Additional occurrences will be ignored, using first typed argument."
              << " This message will be printed in the terminal if flag '--debug' set as 'true'.\n"
              << "  + You can also use your own translations to change this program language to your language."
              << " Follow JSON Objects syntax, you may be successfully change to your language!\n";

    std::cout << " Basic Usage: spell.exe (you can also using flags like above usage).\n"
              << " If you do not provide a context to spell or (and) position of context on Casio's screen with flags, the program will prompt you to enter it.\n";
    std::cout << " If you have provided all required inputs, you can press the buttons on your Casio fx580vnx like this tutorial.\n"
              << " I hope you are successfully!\n";

    // Vietnamese
    std::cout << "Tiếng Việt:\n Dùng trực tiếp (sử dụng cờ): spell.exe [CÁC TÙY CHỌN] [ĐỐI SỐ] -c <nội dung>\n";
    std::cout << " Các cờ        Các tham số       Ý nghĩa\n";
    // --debug
    std::cout << " --debug       true              Cho phép xem app đâng chạy hoặc làm gì\n";
    std::cout << "               false             Ẩn nhật kí khi chạy\n";
    // --help
    std::cout << " --help        <none>            Hiện thông báo này và thoát\n";
    // --version
    std::cout << " --version     <none>            Xem phiên bản của app và thoát\n";
    // -c or -context
    std::cout << " -c            <context>         Nội dung bạn muốn nhập vào để hướng dẫn spell\n";
    std::cout << " -context      <context>         Một cách nhập khác tương tự như cờ '-c'\n";
    // -lang
    std::cout << " -lang         <language>        Chọn ngôn ngữ, các ngôn ngữ nhà phát triển hỗ trợ: Tiếng Việt và Tiếng Anh\n"
              << "                                 Ngôn ngữ sẽ được load trong file có dạng <ngôn ngữ của bạn>.json\n";
    // -p
    std::cout << " -p            Left              Nội dung của bạn sẽ hiển thị ở bên trái màn hình Casio\n"
              << "               Middle            Nội dung của bạn sẽ hiển thị ở bên giữa màn hình Casio\n"
              << "               Right             Nội dung của bạn sẽ hiển thị ở bên phải màn hình Casio\n";
    // Warnings
    std::cout << " Lưu ý:\n  + Tất cả các cờ đều được đặt duy nhất một lần. Các lần tiếp theo sẽ không được đặt, sử dụng đối số đã được đặt lần đầu."
              << " Thông báo này sẽ được in ra màn hình khi cờ '--debug' được đặt là 'true'.\n"
              << "  + Bạn cũng có thể sử dụng bản dịch từ ngôn ngữ của bạn để thay đổi chương trình này sang ngôn ngữ của bạn."
              << " Tuân theo các yêu cầu của JSON dạng Object, bạn có thể thành công để đổi ngôn ngữ chương trình này theo ngôn ngữ của bạn!\n";

    std::cout << " Các dùng cơ bản: spell.exe (bạn cũng có thể kết hợp các cờ có sẵn ở trên).\n"
              << " Nếu bạn không nhập nội dung cần để spell hoặc (và) vị trí của nó trên màn hình, cách này sẽ bắt buộc bạn nhập.\n";
    std::cout << " Nếu bạn đã nhập hết những yêu cầu bắt buộc như trên, tiếp theo bạn cần nhấn các nút trên Casio fx580vnx của bạn như trên màn hình xuất ra.\n"
              << " Tôi hi vọng bạn sẽ thành công!\n";
}

int main(int argc, char** argv){
    // system("chcp 65001 >nul 2>&1"); // For Windows commands
    opts["lang"] = "English";
    opts["errs"] = "0";
    opts["warns"] = "0";

    std::map<std::string, short> called_args = {};

    if (argc > 0){
        JSONObject lang_pack_obj_default(opts["lang"] + ".json");
        lang_pack_obj_default.open();
        lang_pack_obj_default.dump();

        lang_pack_obj = lang_pack_obj_default;
        
        for (int pos = 1; pos < argc; pos++){
            if (std::strcmp(argv[pos], "-lang") == 0){
                if (called_args["-lang"] == 0){
                    if (opts["lang"] != argv[pos + 1]) {
                        // Kiểm tra ngôn ngữ đã được đặt chưa
                        opts["lang"] = argv[pos + 1];
                        JSONObject new_lang_pack(opts["lang"] + ".json");
                        if (!new_lang_pack.open()){
                            std::cout << GetStringByLangPack("7A") << opts["lang"] << GetStringByLangPack("7B") << opts["lang"] << GetStringByLangPack("7C");
                            throw std::runtime_error("Language file not found!");
                        }
                        new_lang_pack.dump();

                        lang_pack_obj = new_lang_pack;
                    }
                    called_args["-lang"]++;
                }
                else if (called_args["-lang"] > 0 && opts["Is Debug Mode"] == "true"){
                    std::cout << GetStringByLangPack("5A");
                    // opts["warns"] = std::stoi(opts["warns"]) + 1;
                }
                pos++; continue;
            }
            if (std::strcmp(argv[pos], "-context") == 0 ||
                std::strcmp(argv[pos], "-c") == 0){
                    if (called_args["-c"] == 0) {
                        opts["Context"] = argv[pos + 1];
                        called_args["-c"]++;
                    } else if (called_args["-c"] > 0 && opts["Is Debug Mode"] == "true") {
                        std::cout << GetStringByLangPack("5B");
                        // opts["warns"] = std::stoi(opts["warns"]) + 1;
                    }
                    if (opts["Context"].length() > 17){
                        std::cout << GetStringByLangPack("1A") << opts["Context"] << GetStringByLangPack("1B");
                        opts["errs"] = std::stoi(opts["errs"]) + 1;
                    }
                    pos++; continue;
            }
            if (std::strcmp(argv[pos], "-p") == 0){
                if (std::strcmp(argv[pos + 1], "Left") != 0 &&
                    std::strcmp(argv[pos + 1], "Middle") != 0 &&
                    std::strcmp(argv[pos + 1], "Right") != 0){
                        std::cout << GetStringByLangPack("2A") << std::string(argv[pos + 1]) << GetStringByLangPack("2B");
                        opts["errs"] = std::stoi(opts["errs"]) + 1;
                } else {
                    if (called_args["-p"] == 0) {
                        opts["Pos In Screen"] = argv[pos + 1];
                        called_args["-p"]++;
                    } else if (called_args["-p"] > 0 && opts["Is Debug Mode"] == "true"){
                        std::cout << GetStringByLangPack("5C");
                        // opts["warns"] = std::stoi(opts["warns"]) + 1;
                    }
                }
                pos++; continue;
            }
            if (std::strcmp(argv[pos], "--debug") == 0){
                if (std::strcmp(argv[pos + 1], "true") != 0 &&
                    std::strcmp(argv[pos + 1], "false") != 0){
                        std::cout << GetStringByLangPack("3A") << std::string(argv[pos + 1]) << GetStringByLangPack("3B");
                        opts["errs"] = std::stoi(opts["errs"]) + 1;
                } else {
                    if (called_args["--debug"] == 0){
                        opts["Is Debug Mode"] = argv[pos + 1];
                        called_args["--debug"]++;
                    } else if (called_args["--debug"] > 0 && opts["Is Debug Mode"] == "true"){
                        std::cout << GetStringByLangPack("5D");
                        // opts["warns"] = std::stoi(opts["warns"]) + 1;
                    }
                }
                pos++;
                continue;
            }
            if (std::strcmp(argv[pos], "--help") == 0){
                HelpScreen();
                return 0;
            }
            if (std::strcmp(argv[pos], "--version") == 0){
                std::cout << GetStringByLangPack("6A") << SPELLER_VERSION << GetStringByLangPack("6B");
                return 0;
            }
            else {
                std::cout << GetStringByLangPack("4A") << argv[pos] << GetStringByLangPack("4B");
                opts["errs"] = std::stoi(opts["errs"]) + 1;
            }
        }
    }
    if (opts.find("Context") == opts.end() || opts["Context"] == "" || opts["Context"].length() > 17){
        if (opts.find("Context") == opts.end()) std::cout << GetStringByLangPack("9");
        else if (opts["Context"] == "") std::cout << GetStringByLangPack("10");
        else if (opts["Context"].length() > 17){
            // Đã gọi
            if (called_args["-c"] > 0) std::cout << GetStringByLangPack("12");
            else std::cout << GetStringByLangPack("11");
        }
        std::cin >> opts["Context"];
        while (opts["Context"] == "" || opts["Context"].length() > 17){
            opts["errs"] = std::stoi(opts["errs"]) + 1;
            std::cout << GetStringByLangPack("11");
            std::cin >> opts["Context"];
        }
    }

    // if (opts["Is Debug Mode"] == "true"){
    //     if (std::stoi(opts["errs"]) > 0){
    //         std::cout << GetStringByLangPack("13");
    //     }
    //     if (std::stoi(opts["warns"]) > 0){
    //         std::cout << GetStringByLangPack("14");
    //     }
    // }
    return 0;
}
