# NikuQBasic



### 型変換ファンクション

|ファンクション|引数|戻り値|説明|
|:--|:--|:--|:--|
|float2int(v:)|v(float):小数値|(int):変換後整数値|floatからintに変換する。|
|str2int(v:)|v(str):文字列値|(int):変換後整数値|strからintに変換する。|
|bool2int(v:)|v(bool):bool値|(int):変換後整数値|boolからintに変換する。|
|int2float(v:)|v(int):整数値|(float):変換後小数値|intからfloatに変換する。|
|str2float(v:)|v(str):文字列値|(float):変換後小数値|strからfloatに変換する。|
|bool2float(v:)|v(bool):bool値|(float):変換後小数値|boolからfloatに変換する。|
|int2str(v:)|v(int):整数値|(str):変換後文字列値|intからstrに変換する。|
|float2str(v:)|v(float):小数値|(str):変換後文字列値|floatからstrに変換する。|
|bool2str(v:)|v(bool):bool値|(str):変換後文字列値|boolからstrに変換する。|
|int2bool(v:)|v(int):整数値|(bool):変換後bool値|intからboolに変換する。|
|float2bool(v:)|v(float):小数値|(bool):変換後bool値|floatからboolに変換する。|
|str2bool(v:)|v(str):文字列値|(bool):変換後bool値|strからboolに変換する。|

### 数学ファンクション

|ファンクション|引数|戻り値|説明|
|:--|:--|:--|:--|
|abs(i:)|i(int):整数値|(int):結果|int型の絶対値を求める。|
|abs(f:)|f(float):小数値|(float):結果|float型の絶対値を求める。|
|max(i1:,i2:)|i1(int):比較1<br>i2(int):比較2|(int):結果|int型の大きい方を求める。|
|max(f1:,f2:)|f1(float):比較1<br>f2(float):比較2|(float):結果|float型の大きい方を求める。|
|min(i1:,i2:)|i1(int):比較1<br>v2(int):比較2|(int):結果|int型の小さい方を求める。|
|min(f1:,f2:)|f1(float):比較1<br>f2(float):比較2|(float):結果|float型の小さい方を求める。|
|sin(x:)|x(float):角度|(float):結果|サインの計算。|
|cos(x:)|x(float):角度|(float):結果|コサインの計算。|
|tan(x:)|x(float):角度|(float):結果|タンジェントの計算。|
|asin(x:)|x(float):-1~1のサイン値|(float):結果|アークサインの計算。|
|acos(x:)|x(float):-1~1のコサイン値|(float):結果|アークコサインの計算。|
|atan(x:)|x(float):-π/2~π/2のタンジェント値|(float):結果|アークタンジェントの計算。|
|atan2(y:,x:)|y(float):y座標<br>x(float):x座標|(float):結果|y/x のアークタンジェントの計算。|
|sinh(x:)|x(float):角度|(float):結果|ハイパボリックサインの計算。|
|cosh(x:)|x(float):角度|(float):結果|ハイパボリックコサインの計算。|
|tanh(x:)|x(float):角度|(float):結果|ハイパボリックタンジェントの計算。|
|cbrt(x:)|x(float):小数値|(float):結果|floatからintに変換する。|
|pow(x:y:)|x(float):小数値<br>y(float):小数値|(float):結果|xのy乗を求める。|
|sqrt(x:)|x(float):小数値|(float):結果|xの平方根を求める。|
|exp(x:)|x(float):小数値|(float):結果|指数関数eのx乗を求める。|
|log(x:)|X(float):小数値|(float):結果|xの自然対数を求める。|
|log10(x:)|x(float):小数値|(float):結果|xの常用対数を求める。|
|deg2rad(deg:)|deg(float):デグリー値|(float):結果|デグリーからラジアンに変換する。|
|rad2deg(rad:)|rad(float):ラジアン値|(float):結果|ラジアンからでグリーに変換する。|
|rand(v:)|v(int):範囲|(int):結果|0〜v-1の乱数を求める。|
|round(x:)|x(float):小数値|(float):結果|floatからintに変換する。|
|floor(x:)|x(float):小数値|(float):結果|xの小数点以下を切り捨て。|
|ceil(x:)|x(float):小数値|(float):結果|xの小数点以下を切り上げ。|
