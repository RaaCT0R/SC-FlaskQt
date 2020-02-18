from flask import Flask
from flask import jsonify
app = Flask(__name__)

class matrix:
    a = 0
    b = 0
    c = 0
    d = 0

    def __init__(self, x, y, z, w):
        self.a = x
        self.b = y
        self.c = z
        self.d = w

    def __mul__(self, other):
        a1 = self.a * other.a + self.b * other.c
        a2 = self.a * other.b + self.b * other.d
        a3 = self.c * other.a + self.d * other.c
        a4 = self.c * other.b + self.d * other.d
        return matrix(a1, a2, a3, a4)

fibo = matrix(1, 1, 1, 0)

def mat_pow(mat, e):
    if (e == 1):
        return mat

    s_mat = mat_pow(mat, int(e / 2))
    if (e % 2):
        return s_mat * s_mat * mat

    return s_mat * s_mat

def fibonacci(n):
    if (n == 0):
	return 0
    if (n == 1 or n == 2):
        return 1

    return mat_pow(fibo, n - 1).a

@app.route('/<int:num>')
def calculator(num):
    ret = {'code': 200, 'message': 'Calculated successfully', 'answer': str(fibonacci(num))}
    return jsonify(ret)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=80)
