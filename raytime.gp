#!/usr/bin/gnuplot
filename = "raytime.txt";
set xlabel "Ray number";
set ylabel "Travel time";
unset key;
plot filename title "Travel times";
pause -1