syms x1 x2 S r df1 df2;
S = 10;
f = x1.^2 + x2.^2 - 12*x1 - 6*x2;
g = x1.^2 + x2.^2 - 16;
x0 = [-7, 7];
eps = 0.8;
gplus = 0.5 * (g + abs(g));
r = 1;
c = 0;

% минимизация с применением метода ньютона
while S > eps
r = 10*r;
fk = f + r*gplus^2;  
df1 = diff(fk,'x1'); %производная по переменной X1
df2 = diff(fk,'x2');
%подставляем значения X0 в производную (f'(x))
res1 = double(subs(df1, {x1, x2},{x0(1), x0(2)}));
res2 = double(subs(df2, {x1, x2},{x0(1), x0(2)}));
%строим вторую производную
ddf1 = diff(df1, 'x1');
ddf2 = diff(df2, 'x2');
%подставляем значение X0 в производную (f''(x))
dres1 = double(subs(ddf1, {x1, x2},{x0(1), x0(2)}));
dres2 = double(subs(ddf2, {x1, x2},{x0(1), x0(2)}));
%-1 степень
d1 = [(dres1)^(-1); (dres2)^(-1)];
%строим X
x = double([x0(1) - d1(1)*res1; x0(2) - d1(2)*res2]);
%критерий остановки 
S = abs(sqrt((x(1) - x0(1))^2 + (x(2) - x0(2))^2));
x0(1) = x(1);
x0(2) = x(2);
c = c + 1;
end

disp('success');
disp(x);
disp(double(subs(fk, {x1, x2}, {x(1), x(2)})));
disp(c);




% тестовая функция
%f = 10*x1.^2 - 4*x1.*x2 + 7*x2^2 - 4*sqrt(5) * (5*x1 - x2) - 16;
%g = (x1 - 1).^2 + (x2 - 3).^2 - 4;
%x0 = [0; -1*sqrt(5)];

