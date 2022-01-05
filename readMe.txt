Pacman - Ex3

Dor Bivas 315557850 
Yarden Agami 207471186

Additions:
	- Full colors support 
	- Very smart ghost strategy - Bfs Algorithm
Notes:

game:
The game is chronological and sync by board name starting from board 01 to 03
Any defective board will be skipped in this order to the followed one.
After losing all souls retry will give you 3 extra brand new souls.

modes:
save mode - if you lose in save mode and you wish to retry you will be saving the new attempt (overwrite)
load \ silent mode will load all saved .steps file by chronological order 01 to 03.
load will run x2 faster and silent x100~ (no sleep at all).

others:
CMD - we allowed "-save -silent" in the cmd acts like normal save.
Exceptions starting with B: refer to the board also they will skip the current defective board.

Formats:
Our .steps format explanation
    /*--- format example:"P:w:G0:0:G1:1:G2:2:G3:0:F:0 or F:5:2:30:20" --- */
    P - pacman followed by w \ x \ d \ s \ a - key press
    Gi - ghost number i followed by her direction in given place 0 \ 1 \ 2 \ 3
    F - fruit followed by 2 cases: 0 fruit is gone at given moment or 5 - 9 fruit val 
    followed by 0 \ 1 \ 2 \ 3 direction and (xx:yy) his position.
    last line in file stends for steps.

Our .result format explanation
   format xxx:0\1
   xxx - current steps event followed by 0 pacman died or 1 pacman finished board alive.

~~Enjoy~~


