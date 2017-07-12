from flask import Flask, g, render_template, request, jsonify
import mysql.connector
import time
from config import load_config


def create_app():
    app = Flask(__name__, static_folder='static', static_url_path='')
    app.config.from_object(load_config())
    print('running under %s config' % app.config['CONFIG_NAME'])
    import os
    print('os.environ.get(MODE) = %s' % os.environ.get('MODE'))

    # 初始化数据库连接
    def connect_db():
        conn = mysql.connector.connect(**app.config['MYSQL_CONFIG'])
        return conn

    # 获得数据库连接
    def get_db():
        if not hasattr(g, 'mysql_db'):
            g.mysql_db = connect_db()
        return g.mysql_db

    # 结束时关闭数据库连接
    @app.teardown_appcontext
    def close_db(error):
        if hasattr(g, 'mysql_db'):
            g.mysql_db.close()

    # 首页
    @app.route('/')
    def main():
        return render_template('index.html')

    @app.route('/getRank')
    def get_rank():
        if request.values.get('my_highest_score'):
            my_score = int(request.values.get('my_highest_score'))
            db = get_db()
            cursor = db.cursor()
            mysql_query = "SELECT * FROM ranking ORDER BY score;"
            cursor.execute(mysql_query)
            result = cursor.fetchall()
            my_rank = 0
            found = False
            for item in result:
                my_rank += 1
                if item[2] == my_score:
                    found = True
                    break

            return jsonify(my_rank=my_rank if found else -1, ranking_list=result)
        else:
            return jsonify(error='No argument')

    @app.route('/newRecord')
    def add_record():
        if request.values.get('player_name') and request.values.get('score') and request.values.get(
                'difficulty') and request.values.get('time'):
            db = get_db()
            cursor = db.cursor()
            mysql_query = "INSERT INTO ranking VALUES (%s,%s,%s,%s,%s)"
            cursor.execute(mysql_query,
                           (request.values.get('player_name') + time.strftime('%Y-%m-%d %X', time.localtime()),
                            request.values.get('player_name'),
                            request.values.get('score'), request.values.get('difficulty'),
                            request.values.get('time')))
            db.commit()
            return jsonify(info='Success')
        else:
            return jsonify(info='Argument error')

    return app


app = create_app()

if __name__ == '__main__':
    app.run(port=8700)
