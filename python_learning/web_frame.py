#!/usr/bin/python3
# -*- coding: utf-8 -*-

from flask import Flask
from flask import request
from flask import render_template
import os
import re

app = Flask(__name__)

@app.route('/', methods=['GET','POST'])
def home():
    filenames=getFilename()
    return render_template('home.html',filenames=filenames)

@app.route('/signin', methods=['GET'])
def signin_form():
    return render_template('form.html')

@app.route('/signin', methods=['POST'])
def signin():
     username = request.form['username']
     password = request.form['password']

     if username=='admin' and password == 'password':
         return render_template('signin-ok.html',username=username)
     return render_template('form.html',message='Bad username or password',username=username)

@app.route('/homework/<filename>')
def rr(filename):
    filename = '/homework/'+filename
    if not re.match('.*\.html',filename):
        with open('templates'+filename,'rb') as f:
            con=f.read()
        return con
    return render_template(filename)

def getFilename():
    f=[]
    for parent,dirnames,filenames in os.walk('./templates/homework'):
        for filename in filenames:
            if re.match('test.*\.html',filename):
                f.append(filename)
    return f


if __name__ == "__main__":
    app.run(debug=True)

