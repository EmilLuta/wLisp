#include "mpc.h"

int main(int argc, char** argv) {
    mpc_parser_t* Adjective = mpc_new("adjective");
    mpc_parser_t* Noun = mpc_new("noun");
    mpc_parser_t* Phrase = mpc_new("phrase");
    mpc_parser_t* BookingDoge = mpc_new("booking_doge");
    mpca_lang(MPCA_LANG_DEFAULT,
        "
            adjective : \"wow\" | \"many\" | \"so\" | \"such\";             \
            noun : \"booking\" | \"Amsterdam\" | \"benefits\" | \"fun\";    \
            phrase : <adjective> <noun>;                                    \
            booking_doge : <phrase>*;                                       \
        ",
        Adjective, Noun, Phrase, BookingDoge);

    mpc_cleanup(4, Adjective, Noun, Phrase, BookingDoge);
}
