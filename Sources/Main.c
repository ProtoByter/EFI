// Copyright (c) 2021 The kOS authors.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software.
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <EFI.h>

EFI_Status kOS_EFI_main(EFI_Handle handle, EFI_System_Table* table)
{
    table->console_out->string_output(table->console_out, L"kOS EFI Bootloader - v0.0.1 - 'SMALL' Version (contains small esolang intepreter)\nYour firmware vendor is: ");
    table->console_out->string_output(table->console_out, table->firmware_vendor);
    table->console_out->string_output(table->console_out, L"\nEnter your code:\n");

    uint64_t out = 0;
    EFI_Protocol_Text_Input_Key key;
    uint16_t key_message[2] = { '\00', '\00' };
    uint16_t i = 0;
    uint16_t program[1024] = { '\00' };
    
    // Input program

    while (true)
    {
        table->services_boot->wait_for_event(0, &table->console_in->wait_for_key, &out);

        table->console_in->read_key(table->console_in, &key);

        key_message[0] = key.unicode_character;
        table->console_out->string_output(table->console_out, key_message);
        if (key_message[0] == L'\n') {
            break;
        }
        else {
            program[i] = key_message[0];
            i++;
        }
    }

    uint16_t a = 0;

    // Run program
    for (uint16_t pc = 0; program[pc] != '\00'; pc++) {
        if (a == 255) a = 0;
        else if (program[pc] == '+') a++;
        else if (program[pc] == '.') {
            key_message[0] = program[pc];
            table->console_out->string_output(table->console_out, key_message);
        }
    } 

    return EFI_Status_Success;
}
