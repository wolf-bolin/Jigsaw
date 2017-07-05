from config.default import Config


class ProductionConfig(Config):
    # App basic config
    CONFIG_NAME = 'production'
    DEBUG = False
    SECRET_KEY = '9*+X{fW^d@62uNHeFXEArkcAh'
    SERVER_NAME = 'every.admirable.one'

    # Database config
    MYSQL_CONFIG = {
        'user': 'ecA4_user',
        'password': 'cVN5Wdz63bVEWm',
        'host': '127.0.0.1',
        'port': '3306',
        'database': 'ecA4',
        'raise_on_warnings': True,
    }
