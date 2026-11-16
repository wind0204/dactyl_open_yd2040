# Dactyl Open - YD2040
I've built a Dactyl Pivot - Open with a bigger build, movable thumb racks, and bolt-screw guides for the tenting feature.
And thought I might as well share some of the details on the internet.

<br>

<img width="4080" height="3060" alt="sideview-microcontroller" src="https://github.com/user-attachments/assets/d662f2e7-cbfd-44f0-9889-d645539f1716" />
WARNING: I think it was very difficult to connect `GP0` to the wire which in turn gets connected to the RJ10 connector `CRJ029-G-TH` when working on the right half-keyboard because the RJ10 connector was blocking the plated holes for `GP0`-`GP2`.

<br>
<br>

<img width="3060" height="4080" alt="topview" src="https://github.com/user-attachments/assets/4a289b91-64ac-405e-a6b6-2791f3635458" />
WARNING: Because of the curvature, the user will often press a button in a diagonal direction instead of the direction of the gravity pull; The keyboard can slip forward/backward/sideways when you press in a diagonal direction too hard.
This means you can't use medium or high actuation-force switches(around 55g+) on every key unless you somehow have obtained secure holds on the keyboard--e.g. very good rubber pad on the feet or a special modification on the feet that enables the keyboard to be attached to a heavy-duty arm.

<br>
<br>

The MCUs I used were good value, I guess. I don't have the electronic knowledge to really evaluate it well. Its name was YD-2040 V1.1;
And the firmware I used was [qmk](https://github.com/qmk/qmk_firmware)

[YD-2040-2022-V1.1-SCH.pdf](https://github.com/user-attachments/files/18221666/YD-2040-2022-V1.1-SCH.pdf)
![YD-2040-2022-V1 1-pinout](https://github.com/user-attachments/assets/6883a729-a481-4f7f-ba5c-ac5f1cfcbeca)
![rough_sketch](https://github.com/user-attachments/assets/957aa809-f999-479f-b7f8-d094a4700436) WARNING: The `BAT54C` is very tiny. I somehow managed to pull it off without a proper magnifier or a secure hold on the board. Take a look at the picture of a `BAT54C` shorted on the input legs at the bottom end of this document.
[pictures and some backstories](https://newsie.social/@Dewry/113452166034299283)

Most of the inspiration and resources came from [this](https://www.printables.com/model/102789-dactyl-flex-w-threaded-tenting), I borrowed a couple of 3d models from it and I also built a few other 3d models via [Dactyl-Pivot](https://github.com/chenfucn/dactyl-pivot) with a bit of modification and then carved them all to attach different parts like the RJ10 module, [Altana](https://github.com/swanmatch/MxLEDBitPCB), the rotary encoder and YD2040.

A couple of keycaps brush against a neighbor keycap very lightly, but that is a negligible issue. Some tileboards had to be shaved cleanly to remove the protruding remnant of bridges.
One tileboard on each thumb rack had to be ground on two sides; One side to make space for the parts of nylon prints where they're fastened by a bolt, and the other side to make space for a neighbor tileboard. In the picture below, you can see that I made a mistake by not taking into account that it had to be inverted from the opposite hand, and then ground another side to correct the mistake:
![not_three_sides_but_just_two](https://github.com/user-attachments/assets/db0d4721-90eb-4994-965c-5756440e5207)
<img width="4032" height="3024" alt="20241204_162831" src="https://github.com/user-attachments/assets/0b3b8b2d-3127-4648-8003-adb36685a566" />


On `qmk` firmware, I made the keyboard emit a blue animated light on the right half whenever the numpad is not behaving as a numpad (Num Lock is off), and a green animated light on the left half whenever capslock is on, using the single-node `WS2812` on YD2040 V1.1; I also made the keyboard write high on the blue LED on the left YD2040 whenever `SECOND_LAYER` is active and on the right YD2040 whenever N-Key Rollover is off.

The minimum cost for such a project, without taking into consideration tools like solder, multimeter, crimper, etc.: https://docs.google.com/spreadsheets/d/1aFUHoXlercC7e-SuZfpWUTReEQ5fsc-MYpa9vlSZMmo/edit?usp=sharing

<br>

You need to short the input legs of the Schottky diode to connect `Vin` and `VBUS`. WARNING: This component is tiny!
<img width="3060" height="4080" alt="shorted_bat54c_input_legs" src="https://github.com/user-attachments/assets/c98f25d6-944b-4ca7-9145-97c99a861d28" />
