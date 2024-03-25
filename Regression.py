#USES R DATASETS:
#https://vincentarelbundock.github.io/Rdatasets/datasets.html

import numpy as np                      #Math and Lin Alg functions
import pandas as pd
import matplotlib.pyplot as plt         #Creates static and interactive graphs
import matplotlib.dates as mdates
import statsmodels.api as sm            #Stats functions
from scipy.optimize import curve_fit

from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error
# from sklearn.model_selection import train_test_split
from sklearn.preprocessing import PolynomialFeatures
# from sklearn.pipeline import make_pipeline

gold_silver = sm.datasets.get_rdataset("GoldSilver", "AER")
df = gold_silver.data

X = mdates.date2num(df.index)
y_gold = df['gold']
y_silver = df['silver']

def quadratic_function(x, a, b, c):
    return a * x**2 + b * x + c

# def quadratic_function(x, a, b, c):
#     # Convert datetime to numeric
#     x_numeric = mdates.date2num(x)
#     return a * x_numeric**2 + b * x_numeric + c

X_numeric = mdates.date2num(df.index)

popt_gold, _ = curve_fit(quadratic_function, X_numeric, y_gold)
a_gold, b_gold, c_gold = popt_gold
y_gold_pred = quadratic_function(X_numeric, a_gold, b_gold, c_gold)

popt_silver, _ = curve_fit(quadratic_function, X_numeric, y_silver)
a_silver, b_silver, c_silver = popt_silver
y_silver_pred = quadratic_function(X_numeric, a_silver, b_silver, c_silver)

residuals_gold = y_gold - y_gold_pred
z_scores_gold = (residuals_gold - residuals_gold.mean()) / residuals_gold.std()
gold_outliers_mask = np.abs(z_scores_gold) > 3  # 3 sds away
gold_outliers = df[gold_outliers_mask]

residuals_silver = y_silver - y_silver_pred
z_scores_silver = (residuals_silver - residuals_silver.mean()) / residuals_silver.std()
silver_outliers_mask = np.abs(z_scores_silver) > 3  # 3 sds away
silver_outliers = df[silver_outliers_mask]

plt.figure(figsize=(10, 6))

plt.scatter(df.index, y_gold, label='Gold Price', color="gold")
plt.plot(df.index, y_gold_pred, color='blue', label='Gold Quadratic Regression Curve')

plt.scatter(df.index, y_silver, label='Silver Price', color="silver")
plt.plot(df.index, y_silver_pred, color='red', label='Silver Quadratic Regression Curve')

plt.scatter(gold_outliers.index, gold_outliers['gold'], color='black', label='Gold Outliers')

plt.scatter(silver_outliers.index, silver_outliers['silver'], color='purple', label='Silver Outliers')

plt.xlabel('Date')
plt.ylabel('Price')
plt.title('Quadratic Regression: Gold vs. Silver Price with Outliers')
plt.legend()

tick_positions = np.linspace(0, len(df.index) - 1, num=10, dtype=int)  # Choose 10 evenly spaced out indices
plt.xticks(tick_positions, df.index[tick_positions], rotation=45, ha='right')  # Set the ticks and labels

plt.grid(True)
plt.tight_layout()  
plt.show()

#R^2 measures how well the regression line approximates the actual point






downsampled_df = df.iloc[::20]  # Select every 20th row

X = mdates.date2num(downsampled_df.index)
y_gold = downsampled_df['gold']
y_silver = downsampled_df['silver']

lagged_gold_prices = pd.DataFrame({'Date': downsampled_df.index, 'Gold_Price': downsampled_df['gold']})
for i in range(1, 4):  
    lagged_gold_prices[f'Gold_Price_Lag_{i}'] = lagged_gold_prices['Gold_Price'].shift(i)

train_size = int(0.7 * len(lagged_gold_prices))
lagged_gold_prices_train = lagged_gold_prices[:train_size]
lagged_gold_prices_test = lagged_gold_prices[train_size:]

lagged_gold_prices_train = lagged_gold_prices_train.dropna()  
X_train = lagged_gold_prices_train.drop(columns=['Date', 'Gold_Price']).values
y_train = lagged_gold_prices_train['Gold_Price'].values

degree = 3  
poly_features = PolynomialFeatures(degree)
X_train_poly = poly_features.fit_transform(X_train)
poly_model = LinearRegression()
poly_model.fit(X_train_poly, y_train)

X_test = lagged_gold_prices_test.drop(columns=['Date', 'Gold_Price']).values
y_test = lagged_gold_prices_test['Gold_Price'].values

X_test_poly = poly_features.transform(X_test)
y_pred_test = poly_model.predict(X_test_poly)

plt.figure(figsize=(10, 6))
plt.scatter(lagged_gold_prices_train['Date'], y_train, label='Training Data')
plt.scatter(lagged_gold_prices_test['Date'], y_test, label='Testing Data')
plt.plot(lagged_gold_prices_test['Date'], y_pred_test, color='green', label='Actual Gold Prices') 

#THE PREDECTION FOLLOWS THE TREND, the real data is sharply different due to unforseen inflation around the late 2000s and 2010s

plt.xlabel('Date')
plt.ylabel('Gold Price')
plt.title('Predcitive Regression Model')
plt.legend()
plt.xticks([])  
plt.grid(False)
plt.show()

mse_test = mean_squared_error(y_test, y_pred_test)
print("Mean Squared Error (Testing):", mse_test)
