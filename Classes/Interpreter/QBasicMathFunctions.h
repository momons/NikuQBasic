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
	static inline vector<QBasicVariableEntity> abs_params();
	static inline QBasicVariableEntity abs_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	static inline vector<QBasicVariableEntity> fabs_params();
	static inline QBasicVariableEntity fabs_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 最大値
	static inline vector<QBasicVariableEntity> max_params();
	static inline QBasicVariableEntity max_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	static inline vector<QBasicVariableEntity> fmax_params();
	static inline QBasicVariableEntity fmax_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 最小値
	static inline vector<QBasicVariableEntity> min_params();
	static inline QBasicVariableEntity min_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	static inline vector<QBasicVariableEntity> fmin_params();
	static inline QBasicVariableEntity fmin_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// サイン
	static inline vector<QBasicVariableEntity> sin_params();
	static inline QBasicVariableEntity sin_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// コサイン
	static inline vector<QBasicVariableEntity> cos_params();
	static inline QBasicVariableEntity cos_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// タンジェント
	static inline vector<QBasicVariableEntity> tan_params();
	static inline QBasicVariableEntity tan_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// アークサイン
	static inline vector<QBasicVariableEntity> asin_params();
	static inline QBasicVariableEntity asin_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// アークコサイン
	static inline vector<QBasicVariableEntity> acos_params();
	static inline QBasicVariableEntity acos_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// アークタンジェント
	static inline vector<QBasicVariableEntity> atan_params();
	static inline QBasicVariableEntity atan_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// アークタンジェント2
	static inline vector<QBasicVariableEntity> atan2_params();
	static inline QBasicVariableEntity atan2_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// ハイパボリックサイン
	static inline vector<QBasicVariableEntity> sinh_params();
	static inline QBasicVariableEntity sinh_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// ハイパボリックコサイン
	static inline vector<QBasicVariableEntity> cosh_params();
	static inline QBasicVariableEntity cosh_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// ハイパボリックタンジェント
	static inline vector<QBasicVariableEntity> tanh_params();
	static inline QBasicVariableEntity tanh_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 平方根
	static inline vector<QBasicVariableEntity> cbrt_params();
	static inline QBasicVariableEntity cbrt_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// へき乗
	static inline vector<QBasicVariableEntity> pow_params();
	static inline QBasicVariableEntity pow_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// ルート
	static inline vector<QBasicVariableEntity> sqrt_params();
	static inline QBasicVariableEntity sqrt_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 乗を求める
	static inline vector<QBasicVariableEntity> exp_params();
	static inline QBasicVariableEntity exp_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 自然対数
	static inline vector<QBasicVariableEntity> log_params();
	static inline QBasicVariableEntity log_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 常用対数
	static inline vector<QBasicVariableEntity> log10_params();
	static inline QBasicVariableEntity log10_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// デグリーからラジアン
	static inline vector<QBasicVariableEntity> deg2rad_params();
	static inline QBasicVariableEntity deg2rad_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// ラジアンからデグリー
	static inline vector<QBasicVariableEntity> rad2deg_params();
	static inline QBasicVariableEntity rad2deg_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 乱数
	static inline vector<QBasicVariableEntity> rand_params();
	static inline QBasicVariableEntity rand_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 四捨五入
	static inline vector<QBasicVariableEntity> round_params();
	static inline QBasicVariableEntity round_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 切り捨て
	static inline vector<QBasicVariableEntity> floor_params();
	static inline QBasicVariableEntity floor_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);
	/// 切り上げ
	static inline vector<QBasicVariableEntity> ceil_params();
	static inline QBasicVariableEntity ceil_qb(QBasic *interpreter, const vector<QBasicVariableEntity> &arg);

};

#endif /* QBasicMathFunctions_h */
