import telebot
from base import Base
from judge import Judge
from requests import Session
from re import compile
bot = telebot.TeleBot(token="1380562718:AAGvzsjol3rtj2UZuIuz2PxpcXDFM-DTcX0")
SID_RE = compile('SID=([\s\S]+?)&')

@bot.message_handler(commands=['start', 'help'])
def send_help(message: telebot.types.Message):
    bot.reply_to(message, "Дарова, пес")


@bot.message_handler(commands=['add_judge'])
def add_judge(message: telebot.types.Message):
    # try:
    args = message.text.split()[1:]
    url, username, password, label = args
    base = Base()
    u_id = str(message.chat.id)

    base.users[message.chat.id] = base.users.get(u_id, [])
    for judge in base.users[u_id]:
        if judge.label == label:
            bot.reply_to(message, "You have judge with that label!")
            return
    base.users[message.chat.id].append(Judge())
    base.users[u_id][-1].username = username
    base.users[u_id][-1].passwords = password
    base.users[u_id][-1].url = url
    base.users[u_id][-1].label = label
    base.save()
    bot.reply_to(message, "successfully added")


@bot.message_handler(commands=['print_judges'])
def print_judges(message: telebot.types.Message):
    try:
        base = Base()
        u_id = str(message.chat.id)
        base.users[message.chat.id] = base.users.get(u_id, [])
        bot.reply_to(message, '\n'.join(map(str, base.users[u_id])))
    except Exception:
        bot.reply_to(message, "Something went wrong!")


@bot.message_handler(func=lambda x: True)
def send_problem(message: telebot.types.Message):
    print('here')
    try:
        base = Base()
        u_id = str(message.chat.id)
        print(message.text)
        args = message.text.split()
        label, contest_id, problem_num = args
        base.users[message.chat.id] = base.users.get(u_id, [])
        document = message.document
        print(document)
        print(bot.get_file(document))
        for judge in base.users[u_id]:
            if judge.label == label:
                s = Session()
                r = s.post(judge.url, {
                    "action_2": "Войти",
                    "contest_id": contest_id,
                    "locale_id": "1",
                    "login": judge.username,
                    "password": judge.passwords,
                    "prob_name": "",
                    "role": "0"
                })
                sid = SID_RE.findall(r.url)[0]
    except Exception as e:
        print(e)




bot.polling()
