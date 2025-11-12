from sklearn.naive_bayes import MultinomialNB
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score
import pandas as pd

# Create a DataFrame with the given data
data = {
    'Outlook': ['Rainy', 'Rainy', 'Overcast', 'Sunny', 'Sunny', 'Sunny', 'Overcast', 'Rainy', 'Rainy', 'Sunny', 'Rainy', 'Overcast', 'Overcast', 'Sunny'],
    'Temperature': ['Hot', 'Hot', 'Hot', 'Mild', 'Cool', 'Cool', 'Cool', 'Mild', 'Cool', 'Mild', 'Mild', 'Mild', 'Hot', 'Mild'],
    'Humidity': ['High', 'High', 'High', 'High', 'Normal', 'Normal', 'Normal', 'High', 'Normal', 'Normal', 'Normal', 'High', 'Normal', 'High'],
    'Windy': ['FALSE', 'TRUE', 'FALSE', 'FALSE', 'FALSE', 'TRUE', 'TRUE', 'FALSE', 'FALSE', 'FALSE', 'TRUE', 'TRUE', 'FALSE', 'TRUE'],
    'Play': ['NO', 'NO', 'YES', 'YES', 'YES', 'NO', 'YES', 'NO', 'YES', 'YES', 'YES', 'YES', 'YES', 'NO']
}

golf = pd.DataFrame(data)

# Convert categorical variables to numerical using one-hot encoding
golf_encoded = pd.get_dummies(golf[['Outlook', 'Temperature', 'Humidity', 'Windy']])

# Combine the numerical features with the target variable
X = pd.concat([golf_encoded, golf['Play']], axis=1)

# Split the data into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(X.drop('Play', axis=1), X['Play'], test_size=0.2, random_state=42)

# Create and train the Multinomial Naive Bayes classifier
bayes_classifier = MultinomialNB()
bayes_classifier.fit(X_train, y_train)

# Make predictions on the test set
y_pred = bayes_classifier.predict(X_test)

# Calculate the accuracy of the model
accuracy = accuracy_score(y_test, y_pred)

print(f"Accuracy: {accuracy * 100:.2f}%")
