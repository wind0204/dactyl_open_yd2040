# Dactyl Open - YD2040
I've built a Dactyl Pivot - Open with bigger build, movable thumb racks, and bolt-screw guides for the tenting feature.
and thought I might as well share some of the details on the internet.

The MCUs I used was good value, I guess. I don't have electronic knowledge to really evaluate it well. its name was YD-2040 V1.1;
And the firmware I used was [qmk](https://github.com/qmk/qmk_firmware)

[YD-2040-2022-V1.1-SCH.pdf](https://github.com/user-attachments/files/18221666/YD-2040-2022-V1.1-SCH.pdf)
![YD-2040-2022-V1 1-pinout](https://github.com/user-attachments/assets/6883a729-a481-4f7f-ba5c-ac5f1cfcbeca)
![rough_sketch-keeb](https://github.com/user-attachments/assets/98f7b280-ba3f-4c0e-90d6-2f0516f1632d)
[pictures and some backstories](https://newsie.social/@Dewry/113452166034299283)

Most of the inspiration and resources came from [this](https://www.printables.com/model/102789-dactyl-flex-w-threaded-tenting), I borrowed a couple of 3d models from it and I also built a few other 3d models via [Dactyl-Pivot](https://github.com/chenfucn/dactyl-pivot) with a bit of modification and then carved them all to attach different parts like the RJ10 module, [Altana](https://github.com/swanmatch/MxLEDBitPCB), the rotary encoder and YD2040.

A couple of keycaps brush against a neighbor keycap very lightly but that is a negligible issue. some tileboards had to be cut cleanly without any protruding remnant of bridge.
One tileboard on each thumb rack had to be ground on two sides; One side to make space for nylon prints to be fastened via bolt, and the other side to make space for the neighbor tileboard. In the picture below you can see that I made a mistake not counting into account that it had to be inverse from the opposite hand and then ground another side to correct the mistake:
![not_three_sides_but_just_two](https://github.com/user-attachments/assets/db0d4721-90eb-4994-965c-5756440e5207)

On qmk firmware, I made the keyboard emit a blue animated light on the right half whenever numlock is on, and a green animated light on the left half whenever capslock is on using the single WS2812 on YD2040 V1.1; I also made the keyboard write high on the blue LED on the left YD2040 whenever SECOND_LAYER is active and on the right YD2040 whenever NKRO is off.

The minimum cost for such a project without taking into consideration the tools like solder, multimeter, crimper, etc.: https://docs.google.com/spreadsheets/d/1aFUHoXlercC7e-SuZfpWUTReEQ5fsc-MYpa9vlSZMmo/edit?usp=sharing
