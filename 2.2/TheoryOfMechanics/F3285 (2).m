
k = 1;
a = 1;
t = 0 : 1 : 100;
f = a./2*(sin(k.*t)-k.*t.*cos(k.*t));
plot(t, f);
