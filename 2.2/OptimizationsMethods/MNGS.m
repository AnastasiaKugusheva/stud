tic %начало отсчета
X0 = [1; 1; 1];
eps = 0.01;
syms S;
S = 1;
syms L;
C=0; %counter
syms ans;
syms p;



syms X1 X2 X3 %переменные по которым будем брать производные
f = 3*X1^2 + 5*X2^2 +4*X3^2 + 2*X1*X2 - X1*X3 - X2*X3 + 7*X1 +X3;
df1 = diff(f,'X1'); %производная по переменной X1
df2 = diff(f, 'X2');
df3 = diff(f, 'X3');




while S > eps
    
  C = C + 1;  
 
%подставляем значения X0 в производную (f'(x))
res1 = subs(df1, {X1, X2, X3},{X0(1,1), X0(2,1), X0(3,1)});
res2 = subs(df2, {X1, X2, X3},{X0(1,1), X0(2,1), X0(3,1)});
res3 = subs(df3, {X1, X2, X3},{X0(1,1), X0(2,1), X0(3,1)});


%строим X
X = [X0(1,1) - L*res1; X0(2,1) - L*res2; X0(3,1) - L*res3];
%подставляем значение X в f
L0 = subs(f, {X1, X2, X3}, {X(1,1), X(2,1), X(3,1)});

% производная по L
Ld = diff(L0, L);
L = solve(Ld);
X = [X0(1,1) - L*res1; X0(2,1) - L*res2; X0(3,1) - L*res3];  
  
  %критерий остановки
 
  fX11 = subs(df1, {X1, X2, X3}, {X(1,1), X(2,1), X(3,1)});
  fX12 = subs(df2, {X1, X2, X3}, {X(1,1), X(2,1), X(3,1)});
  fX13 = subs(df3, {X1, X2, X3}, {X(1,1), X(2,1), X(3,1)}); 
  
  fX1 = [ fX11; fX12; fX13; ];
  S = sqrt((fX11*fX11 + fX12*fX12 + fX13*fX13));

 
   
  
  disp('Continue');
  
  X0(1,1) = X(1,1);
  X0(2,1) = X(2,1);
  X0(3,1) = X(3,1);
  
  res1 = fX11;
  res2 = fX12;
  res3 = fX13;
  syms L;
end

 

  disp(double(X));
  disp(C);   

toc %конец отсчета



 
 






