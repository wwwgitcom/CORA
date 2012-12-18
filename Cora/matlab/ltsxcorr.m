% lts cross correlation


temp = load('dot11n_llts_0.txtxt');
lts1 = temp(1:2:end, 1) + 1i * temp(1:2:end, 2);
temp = load('dot11n_llts_1.txtxt');
lts2 = temp(1:2:end, 1) + 1i * temp(1:2:end, 2);
temp = load('dot11n_llts_2.txtxt');
lts3 = temp(1:2:end, 1) + 1i * temp(1:2:end, 2);
temp = load('dot11n_llts_3.txtxt');
lts4 = temp(1:2:end, 1) + 1i * temp(1:2:end, 2);



lts_local_1 = lts1(1:16);
lts_local_2 = lts2(1:16);
lts_local_3 = lts3(1:16);
lts_local_4 = lts4(1:16);

local_mix = lts_local_1 + lts_local_2 + lts_local_3 + lts_local_4;


% mixlts = lts1 + lts2 + lts3 + lts4;
mixlts = lts1 + lts2 + lts3 + lts4;

local_template = local_mix(1:16);

temp = [ ones(32, 1);
    mixlts;
    ones(32, 1)
    ];

%y = awgn(temp, 30, 'measured');
y = temp;

xorr = zeros(1, length(y));
xorrnorm = zeros(1, length(y));

for i = 1 : length(y) - length(local_template)
    xorr(i) = local_template' * y(i:i+16 - 1);
    xorrnorm(i) = norm(xorr(i))^2 / ( norm(local_template)^2 * norm(y(i:i+16 - 1))^2 );
end


plot(xorrnorm);



for i = 1 : length(y) - length(local_template)
    e = norm(xorr(i:i+15))^2;
   if xorr(i)^2 > e * 0.5
       fprintf('Is peak @ %d\n', i);
   end
end
