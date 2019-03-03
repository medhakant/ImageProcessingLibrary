set title "Boxplot for matrix multiplication of size 100*100" 
set border 2 front linetype -1 linewidth 1.000
set boxwidth 0.5 absolute
set style fill   solid 0.25 border lt -1
unset key
set pointsize 0.5
set style data boxplot
set xtics border in scale 0,0 nomirror norotate  offset character 0, 0, 0 autojustify
set xtics  norangelimit
set xtics('general' 2,'pthreads' 3,'openblas' 4,'mkl' 5)
set ytics border in scale 1,0.5 nomirror norotate  offset character 0, 0, 0 autojustify
set yrange [ 0.00000 : 2000.000 ] noreverse nowriteback   
set datafile separator ","
plot 'data100.csv' using (2):2, '' using (3):3, '' using (4):4, '' using (5):5