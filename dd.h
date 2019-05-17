#ifndef DD_H
#define DD_H

#include <QDir>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <QStringList>
#include <QTimer>
#include <QtDebug>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

namespace Ui {
class DD;
}

class DD : public QMainWindow {
  Q_OBJECT

 public:
  explicit DD(QWidget *parent = nullptr);
  ~DD();

 private slots:
  void on_pushButton_3_clicked();

  void on_pushButton_2_clicked();

  void on_pushButton_4_clicked();

  void on_pushButton_clicked();

  void on_pushButton_5_clicked();

 private:
  Ui::DD *ui;
  QStringList m_DevStringList;
  QString m_ISOString;
  QFileDialog file_iso;
  QTimer *tim;
  QMessageBox ok;

  void findDevises();
  std::string exec(const char *cmd);
  char *buffer;
};

#endif  // DD_H
