// #include <Arduino.h>
// #include <esp32_utilities.h>
// #include <ACAN2517FD.h>

// SystemOnChip esp;
// Terminal terminal;

// //PINS:

// //**IMU**//
// static const byte MPU_9250_SDA = 0;
// static const byte MPU_9250_SCL = 0;

// //**CAN**//
// static const byte MCP2517_SCK = 16; //16
// static const byte MCP2517_SDI = 25; //25
// static const byte MCP2517_SDO = 17; //17
// static const byte MCP2517_CS = 27;  //30
// static const byte MCP2517_INT = 36; //36
// ACAN2517FD can(MCP2517_CS, esp.hspi, MCP2517_INT);

// //Function Definitons
// void canTask(void *parameters);
// void canSendTask(void *parameters);
// void canReceiveTask(void *parameters);

// void setup()
// {
//     esp.uart0.begin(115200);
//     terminal.begin(&esp.uart0);
//     terminal.printMessage(TerminalMessage("Hello",
//                                           "APP", INFO, micros()));
//     disableCore0WDT();
//     xTaskCreatePinnedToCore(canTask,
//                             "CAN", 10000, NULL, 18, NULL, 0);

//     vTaskDelete(NULL);
// }

// void loop()
// {
//     //
// }

// void canTask(void *parameters)
// {
//     long initial_time = micros();
//     TerminalMessage can_error_debug_message;

//     esp.hspi.begin(MCP2517_SCK, MCP2517_SDO, MCP2517_SDI);

//     ACAN2517FDSettings settings(ACAN2517FDSettings::OSC_40MHz, 1000 * 1000, DataBitRateFactor::x1);

//     settings.mDriverReceiveFIFOSize = 200;

//     const uint32_t errorCode = can.begin(settings, []
//                                          { can.isr(); });

//     can_error_debug_message.body = "CAN Bus Error Code = ";
//     can_error_debug_message.body += String(errorCode);
//     can_error_debug_message.system = "CAN";
//     can_error_debug_message.type = ERROR;
//     can_error_debug_message.time = micros();
//     can_error_debug_message.process_time = micros() - initial_time;

//     terminal.printMessage(can_error_debug_message);

//     //   //Send Task
//     //   xTaskCreatePinnedToCore(canSendTask,
//     //                           "CAN_SEND", 200, NULL, 15, NULL, xPortGetCoreID());
//     //   //Receive Task
//     //   xTaskCreatePinnedToCore(canReceiveTask,
//     //                           "CAN_RECEIVE", 200, NULL, 15, NULL, xPortGetCoreID());
//     while (1)
//     {
//         canSendTask((void *)NULL);
//     }
// }

// //Send definition:
// void canSendTask(void *parameters)
// {
//     long initial_time = millis();
//     int messages_per_second = 0;
//     int missed = 0;
//     double send_bandwith = 0;
//     while (millis() < initial_time + 1000)
//     {
//         CANFDMessage frame;
//         frame.id = 100;
//         frame.len = 32;
//         for (uint8_t i = 0; i < frame.len; i++)
//         {
//             frame.data[i] = i * 2;
//         }
//         send_bandwith = frame.len * messages_per_second;
//         const bool ok = can.tryToSend(frame);
//         if (ok)
//         {
//             terminal.printMessage(TerminalMessage("CAN Send Successful", "APP", INFO, micros()));
//             messages_per_second++;
//         }
//         else
//         {
//             terminal.printMessage(TerminalMessage("Buffer Full", "APP", INFO, micros()));
//             missed++;
//         }
//     }
//     terminal.printMessage(TerminalMessage("Messages per second:  " + String(messages_per_second),
//                                           "CAN", INFO, micros(), micros() - initial_time));

//     terminal.printMessage(TerminalMessage("Missed in 1s: " + String(missed),
//                                           "CAN", INFO, micros(), micros() - initial_time));

//     terminal.printMessage(TerminalMessage("Bandwith in MB/s: " + String(send_bandwith / 1000),
//                                           "CAN", INFO, micros(), micros() - initial_time));
//     vTaskDelete(NULL);
// }

// //Receive definition
// void canReceiveTask(void *parameters)
// {
//     long initial_time = millis();
//     int messages_per_second = 0;
//     double receive_bandwith = 0;
//     while (millis() < initial_time + 1000)
//     {
//         CANFDMessage frame;
//         TerminalMessage id_debug_message;
//         TerminalMessage ext_id_debug_message;
//         TerminalMessage data_debug_message;
//         while (can.receive(frame))
//         {
//             //ID
//             messages_per_second++;
//             id_debug_message.body = "[ID:0x ";
//             id_debug_message.body += String(frame.id);
//             id_debug_message.body += " ";
//             id_debug_message.body += String(HEX);
//             id_debug_message.body += "] ";
//             id_debug_message.type = INFO;
//             id_debug_message.system = "CAN";
//             id_debug_message.time = micros();
//             terminal.printMessage(id_debug_message);

//             //EXT ID
//             if (frame.ext)
//             {
//                 ext_id_debug_message.body = "[EXT:";
//                 ext_id_debug_message.body += "YES] ";
//                 ext_id_debug_message.type = INFO;
//                 ext_id_debug_message.system = "CAN";
//                 ext_id_debug_message.time = micros();
//                 terminal.printMessage(ext_id_debug_message);
//             }
//             else
//             {
//                 ext_id_debug_message.body = "[EXT:";
//                 ext_id_debug_message.body += "NO] ";
//                 ext_id_debug_message.type = INFO;
//                 ext_id_debug_message.system = "CAN";
//                 ext_id_debug_message.time = micros();
//                 terminal.printMessage(ext_id_debug_message);
//             }

//             //DATA
//             data_debug_message.body = " DATA = ";
//             for (uint8_t i = 0; i < frame.len; i++)
//             {
//                 data_debug_message.body += String(frame.data[i]);
//                 data_debug_message.body += " ";
//             }
//             data_debug_message.body += " ";
//             data_debug_message.system = "CAN";
//             data_debug_message.type = INFO;
//             data_debug_message.time = micros();
//             terminal.printMessage(data_debug_message);
//         }
//         receive_bandwith = frame.len * messages_per_second;
//     }
//     terminal.printMessage(TerminalMessage("Messages per second:  " + String(messages_per_second),
//                                           "CAN", INFO, micros(), micros() - initial_time));

//     terminal.printMessage(TerminalMessage("Bandwith in MB/s: " + String(receive_bandwith / 1000),
//                                           "CAN", INFO, micros(), micros() - initial_time));
//     vTaskDelete(NULL);
// }