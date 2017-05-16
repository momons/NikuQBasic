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
	static vector<QBasicVariableEntity> abs_params();
	static QBasicVariableEntity abs_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	static vector<QBasicVariableEntity> fabs_params();
	static QBasicVariableEntity fabs_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 最大値
	static vector<QBasicVariableEntity> max_params();
	static QBasicVariableEntity max_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	static vector<QBasicVariableEntity> fmax_params();
	static QBasicVariableEntity fmax_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 最小値
	static vector<QBasicVariableEntity> min_params();
	static QBasicVariableEntity min_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	static vector<QBasicVariableEntity> fmin_params();
	static QBasicVariableEntity fmin_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// サイン
	static vector<QBasicVariableEntity> sin_params();
	static QBasicVariableEntity sin_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// コサイン
	static vector<QBasicVariableEntity> cos_params();
	static QBasicVariableEntity cos_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// タンジェント
	static vector<QBasicVariableEntity> tan_params();
	static QBasicVariableEntity tan_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// アークサイン
	static vector<QBasicVariableEntity> asin_params();
	static QBasicVariableEntity asin_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// アークコサイン
	static vector<QBasicVariableEntity> acos_params();
	static QBasicVariableEntity acos_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// アークタンジェント
	static vector<QBasicVariableEntity> atan_params();
	static QBasicVariableEntity atan_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// アークタンジェント2
	static vector<QBasicVariableEntity> atan2_params();
	static QBasicVariableEntity atan2_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// ハイパボリックサイン
	static vector<QBasicVariableEntity> sinh_params();
	static QBasicVariableEntity sinh_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// ハイパボリックコサイン
	static vector<QBasicVariableEntity> cosh_params();
	static QBasicVariableEntity cosh_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// ハイパボリックタンジェント
	static vector<QBasicVariableEntity> tanh_params();
	static QBasicVariableEntity tanh_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 平方根
	static vector<QBasicVariableEntity> cbrt_params();
	static QBasicVariableEntity cbrt_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// へき乗
	static vector<QBasicVariableEntity> pow_params();
	static QBasicVariableEntity pow_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// ルート
	static vector<QBasicVariableEntity> sqrt_params();
	static QBasicVariableEntity sqrt_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 乗を求める
	static vector<QBasicVariableEntity> exp_params();
	static QBasicVariableEntity exp_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 自然対数
	static vector<QBasicVariableEntity> log_params();
	static QBasicVariableEntity log_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 常用対数
	static vector<QBasicVariableEntity> log10_params();
	static QBasicVariableEntity log10_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// デグリーからラジアン
	static vector<QBasicVariableEntity> deg2rad_params();
	static QBasicVariableEntity deg2rad_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// ラジアンからデグリー
	static vector<QBasicVariableEntity> rad2deg_params();
	static QBasicVariableEntity rad2deg_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 乱数
	static vector<QBasicVariableEntity> rand_params();
	static QBasicVariableEntity rand_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 四捨五入
	static vector<QBasicVariableEntity> round_params();
	static QBasicVariableEntity round_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 切り捨て
	static vector<QBasicVariableEntity> floor_params();
	static QBasicVariableEntity floor_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 切り上げ
	static vector<QBasicVariableEntity> ceil_params();
	static QBasicVariableEntity ceil_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);

};

#endif /* QBasicMathFunctions_h */
