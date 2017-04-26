//
//  QBasicMathFunctions.h
//  NikuQBasic
//
//  Created by HaraKazunari on 2017/03/20.
//
//

#ifndef QBasicMathFunctions_h
#define QBasicMathFunctions_h

using namespace std;

class QBasic;
class QBasicStatementEntity;
class QBasicVariableEntity;

/// スクリプト Mathサブ関数群
class QBasicMathFunctions final {
public:
	
	/**
	 *  ステートメントを作成
	 *
	 *  @return 文字操作ステートメント
	 */
	static unordered_map<string, QBasicStatementEntity> buildStatements();

	/**
	 *  スクリプト用ステートメント
	 *  @param interpreter 親クラス
	 *  @param arg         引数
	 *  @return 戻り値
	 */
	/// 絶対値
	static QBasicVariableEntity abs_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 最大値
	static QBasicVariableEntity max_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 最小値
	static QBasicVariableEntity min_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// サイン
	static QBasicVariableEntity sin_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// コサイン
	static QBasicVariableEntity cos_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// タンジェント
	static QBasicVariableEntity tan_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// アークサイン
	static QBasicVariableEntity asin_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// アークコサイン
	static QBasicVariableEntity acos_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// アークタンジェント
	static QBasicVariableEntity atan_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// アークタンジェント2
	static QBasicVariableEntity atan2_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// ハイパボリックサイン
	static QBasicVariableEntity sinh_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// ハイパボリックコサイン
	static QBasicVariableEntity cosh_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// ハイパボリックタンジェント
	static QBasicVariableEntity tanh_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 平方根
	static QBasicVariableEntity cbrt_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// へき乗
	static QBasicVariableEntity pow_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// ルート
	static QBasicVariableEntity sqrt_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 乗を求める
	static QBasicVariableEntity exp_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 自然対数
	static QBasicVariableEntity log_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 常用対数
	static QBasicVariableEntity log10_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// デグリーからラジアン
	static QBasicVariableEntity deg2rad_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// ラジアンからデグリー
	static QBasicVariableEntity rad2deg_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 乱数
	static QBasicVariableEntity rand_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 四捨五入
	static QBasicVariableEntity round_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 切り捨て
	static QBasicVariableEntity floor_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 切り上げ
	static QBasicVariableEntity ceil_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);

};

#endif /* QBasicMathFunctions_h */
