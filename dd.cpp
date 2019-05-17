#include "dd.h"
#include "ui_dd.h"

DD::DD(QWidget* parent) : QMainWindow(parent), ui(new Ui::DD) {
  ui->setupUi(this);
  findDevises();
  ui->log->setText("Hello DD!");
  tim = new QTimer;
  tim->setInterval(1000);
  buffer = new char[500];
}

DD::~DD() {
  delete tim;
  delete[] buffer;
  delete ui;
}

void DD::findDevises() {
  const QString nameFilter = "sd*";
  QDir DevDir("/dev", nameFilter, QDir::Name, QDir::System);
  if (m_DevStringList != DevDir.entryList()) {
    m_DevStringList = DevDir.entryList();
    ui->inputDev->clear();
    if (m_DevStringList.empty()) {
      ui->inputDev->addItem("not found");
    } else {
      ui->inputDev->addItems(m_DevStringList);
    }
  }
}

void DD::on_pushButton_3_clicked() {
  m_ISOString = file_iso.getOpenFileName();
  ui->set_iso->setText(m_ISOString);
}

void DD::on_pushButton_2_clicked() {  //Запись
  QString sudo("sudo");
  QString util(" dd");
  QString arg_1(" if=");
  QString arg_2(" of=");
  QString arg_3(" bs=1M");
  QString arg_p("/dev/");
  QString arg_dev(ui->inputDev->currentText());
  QString iso(ui->set_iso->toPlainText());
  QString cmd = sudo + util + arg_1 + iso + arg_2 + arg_p + arg_dev + arg_3;
  ui->log->setText(cmd);
  std::system(cmd.toStdString().data());
  ok.open();
}

void DD::on_pushButton_4_clicked() {
  QString sudo("sudo");
  QString util(" umount");
  QString arg_p(" /dev/");
  QString arg_1("1");
  QString arg_dev(ui->inputDev->currentText());
  QString cmd = sudo + util + arg_p + arg_dev + arg_1;
  ui->log->setText(cmd);
  std::system(cmd.toStdString().data());
  ok.open();
}

void DD::on_pushButton_clicked() {  // Чтение
  QString sudo("sudo");
  QString util(" dd");
  QString arg_1(" if=");
  QString arg_2(" of=");
  QString arg_3(" bs=1M count=4000");
  QString arg_p("/dev/");
  QString arg_dev(ui->inputDev->currentText());
  QString iso(ui->name_out_file->toPlainText());
  QString cmd = sudo + util + arg_1 + arg_p + arg_dev + arg_2 + iso + arg_3;
  ui->log->setText(cmd);
  std::system(cmd.toStdString().data());
  ok.open();
}

void DD::on_pushButton_5_clicked() {
  QString util(" lsblk|grep s");
  QString arg_dev(ui->inputDev->currentText());
  QString cmd = util;
  ui->log->setText(cmd.toStdString().data());
  std::string ls = exec(const_cast<const char*>(cmd.toStdString().data()));
  ui->log->setText(ls.data());
}

std::string DD::exec(const char* cmd) {
  std::array<char, 128> buffer;
  std::string result;
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
  if (!pipe) {
    throw std::runtime_error("popen() failed!");
  }
  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    result += buffer.data();
  }
  return result;
}
