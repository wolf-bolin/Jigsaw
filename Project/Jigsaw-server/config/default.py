class Config(object):
    # App basic config
    CONFIG_NAME = 'default'
    DEBUG = True
    SECRET_KEY = 'development_key'
    SERVER_NAME = 'localhost:8700'

    # Database config
    MYSQL_CONFIG = {
        'user': 'database_user',
        'password': 'database_password',
        'host': '127.0.0.1',
        'port': '6666',
        'database': 'everyclass',
        'raise_on_warnings': True,
    }
