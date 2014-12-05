tic %начало отсчета
X0 = [-7; 7];
eps = 0.05;
syms S;
S = 1;
syms L;
C=1; 
syms ans;
syms p;
syms Y;



syms X1 X2 %переменные по которым будем брать производные
f = (X1^2 + X2 -11)^2 + (X1 + X2^2 - 7)^2;
df1 = diff(f,'X1'); %производная по переменной X1
df2 = diff(f,'X2');


i=0;

counter = 1;
syms pX pY
pX(counter,1) = double(X0(1,1));
pY(counter,1) = double(X0(2,1));
counter = counter + 1;

Y0(1,1) = 1;
Y0(2,1) = 1;
 
while S > eps
  i=0;
 
%делаем 2 шага по методу наискорейшего градиентного спуска (MNGS)
while i < 2
   i = i + 1;
   syms L;
   syms K; 
   
%подставляем значения Y0 в производную (f'(x))
res1 = subs(df1, {X1, X2},{Y0(1,1), Y0(2,1)});
res2 = subs(df2, {X1, X2},{Y0(1,1), Y0(2,1)});
%строим Y
Y = [Y0(1,1) - L*res1; Y0(2,1) - L*res2];
%подставляем значение Y в f
L0 = subs(f, {X1, X2}, {Y(1,1), Y(2,1)});
% нахождение минимума методом золотого сечения
syms a b c d;
a = -2;
b = 3;
c = a + (b - a) * (3 - sqrt(5))/2;
d = a + (b - a) * (sqrt(5) - 1)/2;
while (abs(a - b) > 2 * eps) 
fc = double(subs(L0, {L}, c));
fd = double(subs(L0, {L}, d));
if fc <= fd
    b = d;
    d = c;
    c = a + (b - a) * (3 - sqrt(5))/2;
else
    a = c;
    c = d;
    d = a + (b - a) * (sqrt(5) - 1)/2;
end    
end
K = (a + b) / 2;    
Y = ([Y0(1,1) - K*res1; Y0(2,1) - K*res2]);         
Y0(1,1) = Y(1,1);
Y0(2,1) = Y(2,1);
end    

C = C + 1;  
syms L;
syms K;
%строим X
X = [X0(1,1) + K*(Y(1,1) - X0(1,1)); X0(2,1) + K*(Y(2,1) - X0(2,1))];
%подставляем значение X в f
L0 = subs(f, {X1, X2}, {X(1,1), X(2,1)});
% нахождение минимума методом золотого сечения
syms a b c d;
a = -2;
b = 3;
c = a + (b - a) * (3 - sqrt(5))/2;
d = a + (b - a) * (sqrt(5) - 1)/2;
while (abs(a - b) > 2 * eps) 
fc = double(subs(L0, {K}, c));
fd = double(subs(L0, {K}, d));
if fc <= fd
    b = d;
    d = c;
    c = a + (b - a) * (3 - sqrt(5))/2;
else
    a = c;
    c = d;
    d = a + (b - a) * (sqrt(5) - 1)/2;
end    
end
K = (a + b) / 2;   
X = [X0(1,1) + K*(Y(1,1) - X0(1,1)); X0(2,1) + K*(Y(2,1) - X0(2,1))];  
%критерий остановки
S = double(abs(subs(f, {X1, X2},{X(1,1), X(2,1)}) - (subs(f, {X1, X2},{X0(1,1), X0(2,1)}))));
X0(1,1) = X(1,1);
X0(2,1) = X(2,1);

pX(counter,1) = double(X(1,1));
pY(counter,1) = double(X(2,1));
counter = counter + 1;
end

disp(double(X));
disp(C);   

toc %конец отсчета

hold on

x = -10 : .2 : 10;  
[CX1, CX2] = meshgrid(x);
Z = (CX1.^2 + CX2 -11)^2 + (CX1 + CX2.^2 -7)^2;
contour(CX1, CX2, Z, 4);

plot(pX, pY, '-or');

hold off


 
 






