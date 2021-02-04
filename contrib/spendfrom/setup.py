from distutils.core import setup
setup(name='BTCOspendfrom',
      version='1.0',
      description='Command-line utility for bitcoinoil "coin control"',
      author='Gavin Andresen',
      author_email='gavin@bitcoinoilfoundation.org',
      requires=['jsonrpc'],
      scripts=['spendfrom.py'],
      )
