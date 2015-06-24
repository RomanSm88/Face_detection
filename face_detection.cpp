#include "face_detection.h"

Face_detection::Face_detection(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags), haarcascade_frontalface_alt2("./Haar/haarcascade_frontalface_alt2.xml"),
	file(0), time(0), height_pix(0.0), width_pix(0.0), fps_detect(0), fps_time(0), fps_summ(0)
{
	// ������������� ��������� ���� ��� ���������� �������
		ui.setupUi(this);
	
	// ��������� ������ ����� �� �����
		haar_cascade = new CascadeClassifier(haarcascade_frontalface_alt2);
	

	// ��������� ��������� ���������� ����� �����
		colors << cvScalar(0.0,0.0,255.0) << cvScalar(0.0, 128.0, 255.0)
			<< cvScalar(0.0,255.0,255.0) << cvScalar(0.0,255.0,0.0)
			<< cvScalar(255.0,128.0,0.0) << cvScalar(255.0,255.0,0.0)
			<< cvScalar(255.0,0.0,0.0) << cvScalar(255.0,0.0,255.0);
	
	// ������� ������ ��� ������ ������������� ����������� � ������� ���� ���������
		qpix = new QPixmap();
	
	// ������� ������������ ������
		time_zaderjka = new QTime();
	// �������� ����������: QRadioButton
	// ������ ����������� �� ���������
		ui.radioButton_2->setChecked(true); // �� ��������� � �������� ��������� ����� ����

	// ����� ������������� ��� ��������� ��������� �����������
		connect(ui.radioButton, SIGNAL(pressed()), this, SLOT(radio_button_camera()));
		connect(ui.radioButton_2, SIGNAL(pressed()), this, SLOT(radio_button_fail()));
	

	// ����� ������������ ��� ������ � ������
	// ����� ����������� ��� ������� �� ������ - "�����"
		connect(ui.toolButton, SIGNAL(clicked()), this, SLOT(knopka_obzor()));
	// ����� ����������� ��� ������� ���������������
		connect(ui.knopka, SIGNAL(clicked()), this, SLOT(knopka_play()));

	
}

void Face_detection::stop_video()
{
	// ���������� ������� ������
		fps_detect = 0;

		if (time)
			time->stop();
		if (fps_time)
			fps_time->stop();

		if (file)
			file->~VideoCapture();

	// �������� ��� �������� � ��������x ����������
		ui.lineEdit->clear();
		ui.label->clear();
		ui.SizeVideo_1->clear();
		ui.Size_Video_2->clear();
		ui.FPS_1->clear();
		ui.FPS_2->clear();
		ui.label_7->clear();
		ui.label_9->clear();
}

void Face_detection::en_ds_knopci(bool znach)
{
	
		ui.knopka->setEnabled(znach);
		ui.lineEdit->clear();
		ui.lineEdit->setEnabled(znach);
		ui.toolButton->setEnabled(znach);
		ui.label_2->setEnabled(znach);
		ui.label_3->setEnabled(znach);
		ui.label_8->setEnabled(znach);
		ui.checkBox_2->setEnabled(znach);
}

void Face_detection::knopka_play()
{
	// ��������� ���� �� �������� ������ ��� ���� � ��� �� ������� ������, ���� ��� ��������� ������, ���������� �� �����
	if (file && time)
	{
		// ������������� ������
		time->stop();
		fps_time->stop();
		// �������� ���������� ������ VideoCapture � ����������� ������
		file->~VideoCapture();
	}
	// ��������� ���� � �����
		file = new VideoCapture(fileName);

	// ��������, ������� �� ������� �����
		if (!proverka_otkrxtiy())
			return;


	// ����������� ������� �����: ������� ������, ����������.
	// ��� ������������� �������� �������� ����� - ���������� ����������, ��� ���� ����� ������� ����� �� ��������� � ��������� 
	// ������������ ����� � ������� �������� ���� ���������

	if (file->get(CV_CAP_PROP_FRAME_WIDTH) != 720 && file->get(CV_CAP_PROP_FRAME_HEIGHT) != 480)
	{
		ui.label_7->clear();
		ui.label_9->clear();
	// ��� ��� ����������� � ���������
		ui.SizeVideo_1->setText(QString::number(file->get(CV_CAP_PROP_FRAME_WIDTH)) + "x" + QString::number(file->get(CV_CAP_PROP_FRAME_HEIGHT))+ "p"); // ����������
	// ������� ������
		ui.FPS_1->setText(QString::number(file->get(CV_CAP_PROP_FPS))+"k/s"); 
		// �������� ������� ����� �� ����������� ��� SD 720x480
		// ��������� �������� ���������� SD � ���������� ���������x ��� ���������� ���������
		width_pix = 720;
		height_pix = 480;
		// ���������� ���������� ���������� � ���������
		ui.Size_Video_2->setText(QString::number(width_pix) + "x" + QString::number(height_pix) + "p");
	} else
	{
		// ��� ��� ����������� � ���������
		ui.SizeVideo_1->setText(QString::number(file->get(CV_CAP_PROP_FRAME_WIDTH)) + "x" + QString::number(file->get(CV_CAP_PROP_FRAME_HEIGHT))+ "p"); // ����������
		ui.FPS_1->setText(QString::number(file->get(CV_CAP_PROP_FPS))); // ������� ������

		// ��������� �������� ���������� � ���������� ���������� ��� ���������� ���������
		width_pix = file->get(CV_CAP_PROP_FRAME_WIDTH);
		height_pix = file->get(CV_CAP_PROP_FRAME_HEIGHT);

		// ���������� ���������� ���������� � ���������
		ui.Size_Video_2->setText(QString::number(width_pix) + "x" + QString::number(height_pix));
	}


	// ������������� ������ - �������� ������
		time = new QTimer(this);
	// ������������� ������ ��� ���������� ������� ������
		fps_time = new QTimer(this); 
		connect(fps_time, SIGNAL(timeout()), this, SLOT(fps_count()));  // ����������� ������ �� ������, ������ 1000�� = 1� � �������� ������ ���������
		fps_time->start(1000); 
	// ���������� ������� � �����
	// ��� ������� �� ������ ���������� ����������������
		connect (time, SIGNAL(timeout()), this, SLOT(on_actionCapture_opencv()));
	// ������������� ��������� �������� ������ ������ on_actionCapture_opencv()
	// ��������� ��������� ������������ �� �������: ��������� 1�������, ���������� � ������������ = 1000��, � ������� ��������������� ����� (FPS)
		time->start(1000/file->get(CV_CAP_PROP_FPS));
	
	// ��������� ������ ��� ������ ������� ���������� ���������
		time_zaderjka->restart();
	
}
// �� ���������������� ��������
void Face_detection::face_search(cv::Mat &src, double width, double height)
{
	QImage qmag;

	// ���������  ���������� ����� �� ���������� width_pix, height_pix
	cv::resize(src, src, Size(width,height), INTER_LINEAR);


	// ��������� �������� �������� ������, ���� ���-���� �������
	if (ui.checkBox->isChecked())
	{

		haar_cascade->detectMultiScale(
			src, // ��������
			vector_objekt,  // ��������, ����� ��������� �� ����������� � ���������� �������� �������
			1.3, // ���������� ���������� ���������
			3, // ����������� ����� �������� ���������, �������� ������� ����� ��������� � �������� �������: ��� ���� ��� ���?
			CV_HAAR_DO_CANNY_PRUNING, // ���������, ��������� ���������� ������� �� �����������, � ������� ���� �� ����� ���� �� ��� ����� ���������������.
			Size(30,30) // ������ "����������� ����", ��� ����������� ������� �������������� ������ �����������.
			);

		// ��������� � ������������ �������������� � �����.
		for (int i = 0; i < vector_objekt.size(); i++)
		{
			rectangle(src, vector_objekt[i], Scalar(colors[i%8]), 2); 
		}
	}

	// ��������� ����������� ����������� OpenCV ���������, ������������ ������ � ������ Qt
	qmag = QImage((const uchar *)src.data, src.cols, src.rows, QImage::Format_RGB888).rgbSwapped();
	// �������� ����������� ����� fromImage, ��� �������������� ���� QImage, � ��� QPixmap
	*qpix = QPixmap::fromImage(qmag);

	// ������� ������������ ����������� � ���� ���������
	ui.label->setPixmap(*qpix);
}
// ���������������� ��������
void Face_detection::face_search(cv::Mat &src, cv::Mat &temp , double width, double height)
{

	QImage qmag;

	// ���������  ���������� ����� �� ���������� width_pix, height_pix
		cv::resize(src, src, Size(width,height), INTER_LINEAR);
	

	// ��������� �������� �������� ������, ���� ���-���� �������
	if (ui.checkBox->isChecked())
	{
 
	//��������� ���������� ����������� �� 50%
	// ����������� � ����������� ����������� ��������� � ������� - tmp
			cv::resize(src, temp, Size(), 0.5, 0.5);

	// ����������� ��������� ���� �� ����������� � ������� ������� �����
	// ��������� ��� �������� ��������� - ������, �� ����������� ���������� STL
	// ������� ����������� ���� - 30x30 �������. 
		haar_cascade->detectMultiScale(
			temp, // ��������
			vector_objekt,  // ��������, ����� ��������� �� ����������� � ���������� �������� �������
			1.3, // ���������� ���������� ���������
			3, // ����������� ����� �������� ���������, �������� ������� ����� ��������� � �������� �������: ��� ���� ��� ���?
			CV_HAAR_DO_CANNY_PRUNING, // ���������, ��������� ���������� ������� �� �����������, � ������� ���� �� ����� ���� �� ��� ����� ���������������.
			Size(30,30) // ������ "����������� ����", ��� ����������� ������� �������������� ������ �����������.
			);

	// ��������� � ������������ �������������� � �����.
	// �� �������� ����������� �������� �������������, ��������� rectangle() �� ���������� OpenCV. ���� ������ ���������������, ��������
	// ������� ��������� - Scalar(), ��������� ��������� - ����, ������� �����.
	// ���� ������ �������������� �������� �� ������ - colors, ������� ��� ��������� � ������������.
		for (int i = 0; i < vector_objekt.size(); i++)
			{
	// �������� ��� ������������.
	// ��� ��� ����������� ������� ������������ ������� ����� ������ = 1/2 �� ������������� �����������, ��
	// ���������� ������������ �������� ��������� � 2 ����, ������������� ���������� ���������� ��������
	// �� "���������" ����������� ����� ��������� � ��� ����.
				vector_objekt[i].x = vector_objekt[i].x * 2;
				vector_objekt[i].y = vector_objekt[i].y * 2;
	// ����������� ������ � ������ �������� � 2 ����.
				vector_objekt[i].width = vector_objekt[i].width * 2;
				vector_objekt[i].height = vector_objekt[i].height * 2;
	// ������ ������� �� ��� ������ �����������, ��� ���� ���������� ����. ���� ����� ����� �� ������ �olors. 
	// ����� ��������, � ������ ��������� ��� �������� �� �������� i/8, ������� ������ �������� ����� 2.
				rectangle(src, vector_objekt[i], Scalar(colors[i%8]), 2); 
			}
	}
	

	// ��������� ����������� ����������� OpenCV ���������, ������������ ������ � ������ Qt
		qmag = QImage((const uchar *)src.data, src.cols, src.rows, QImage::Format_RGB888).rgbSwapped();
	// �������� ����������� ����� fromImage, ��� �������������� ���� QImage, � ��� QPixmap
		*qpix = QPixmap::fromImage(qmag);

	// ������� ������������ ����������� � ���� ���������
		ui.label->setPixmap(*qpix);
	
	
		
}

void Face_detection::on_actionCapture_opencv()
{
	// ������������� ������ Mat �� OpenCV � �������� ���������� ��� �����
		Mat mat_img;

		// ������� ��������� �������
		Mat tmp;
	
	// ���� ����� ������ ���, �� �� ���� ����������� "��" ��� ����� ������������� � ������, ��� ������ � ��������� ������� � ������ �� �����
	// ���������������
		if (!file->read(mat_img))
		{
			fps_time->stop();
			time->stop();
	// ��������� �������� ������� ����������
			int time_run = time_zaderjka->elapsed();
	// ��������� ������� ������ ����� ����� ���������			
			float fps_2 = fps_summ/(time_run/1000);
	// ���������� ����� ������ � ������� ��������� � ���� ���������
			fps_summ = 0;
			ui.label_7->setText(QString::number(fps_2)+"k/s");
	// ���������� �������� ������ �����������
	// �� �������:  Latentnosty = (fps_original - fps_posle_obrabotki)*(fps_original/100)
			float fps_original = file->get(CV_CAP_PROP_FPS);
			float Latentnosty = (fps_original - fps_2)*(fps_original/100);
	// ������ ��������� � ������� ���� ���������
			ui.label_9->setText(QString::number(Latentnosty) +"%");
		
		} else
		{
	// ���� ����������� �� ���������
			if (!ui.checkBox_2->isChecked()) 
			face_search(mat_img, tmp, width_pix, height_pix);
			else
	// ���� ����������� ���������
			face_search(mat_img, width_pix, height_pix);
	
	// ����������� �������� �������� ������, ��� ����������� �������
			fps_detect++;
			
		
		}

	// ����������� �������
		tmp.release();
		mat_img.release();	
}
void Face_detection::on_actionCapture_opencv_camera()
{
	// ������������� ������ Mat �� OpenCV � �������� ���������� ��� �����
		Mat mat_img;
		Mat tmp;
	// ��������� ���� � ���������
		*file >> mat_img;

	face_search(mat_img, tmp); // �������� ����� �������������� ����
	// ������� ������
		fps_detect++;
	// ����������� �������
		mat_img.release();
		tmp.release();
}
void Face_detection::fps_count()
{	
	
	// ������������ ������
		fps_summ += fps_detect;
		ui.FPS_2->setText(QString::number(fps_detect)+"k/s");
	// �������� ������� ������
		fps_detect = 0;
}

void Face_detection::knopka_obzor()
{
		QString Name = QFileDialog::getOpenFileName(this, tr("Open File"), "");

		if (Name.isEmpty()) {
			QMessageBox::critical(this, tr("Error"), tr("Fail not found!"));
			return;
		}
	// ����� toLocal8Bit(), ������ QString, ���������� �������������� ������ � ������� QByteArray - ������ ����, ��� �������� �� ���������. 
	// ��� ��� ����� std::string  ��������� �� ���� ����� ���� ��������������� ����, �� �������������� ���� � ��������� �������� std::string
	// ������������ ������������� ���������� ������ std::string. ������ ������ ����������� ������������� ���� �� ������ ���������, �� ���� ����
	// ��� �� �������� ���������� ��������� �������� ������������� � ������������ �������.
		fileName = Name.toLocal8Bit();

	// ������������� �������� ���������� Name � ���� ����� ������: LineEdit
		ui.lineEdit->setText(Name);

}

void Face_detection::radio_button_camera()
{
	
		stop_video(); // ���������� �����-����� �������� �� ��������� �����
		en_ds_knopci(false);

	// ��������� ����� � ������
		file = new VideoCapture(0); // ���������� ����� ����������� �� ��������. ������ ���������� ����������� � �������
	
	// ��������, ������� �� ������� �����
		if (!proverka_otkrxtiy())
				return;

	// ������������� ������ - �������� ������
		time = new QTimer(this);
	// ������������� ������ ��� ���������� ������� ������
		fps_time = new QTimer(this); // ������ ������ � ���������� ������������ 1�������

	connect(fps_time, SIGNAL(timeout()), this, SLOT(fps_count()));  // ���������� ������� �� ������, ������ 1000�� = 1� � �������� ������ ���������
		fps_time->start(1000); // ������ ������� ������ fps_count ��������� � 1�������
		
	// ������ ������� ������ on_actionCapture_opencv() ������������ ��������� ��������������� ������� time->start()
		connect (time, SIGNAL(timeout()), this, SLOT(on_actionCapture_opencv_camera()));
	// ������������� ��������� �������� ������ ������ on_actionCapture_opencv()
	// ��������� ��������� ������������ ��� ��������� 1000 = 1������� � �������� ������� ������
		time->start(1000/file->get(CV_CAP_PROP_FPS));
		
		

}

void Face_detection::radio_button_fail()
{
	// ���������� ����� ����� �������� �� ��������� �����
		stop_video(); 
		en_ds_knopci(true);
}

bool Face_detection::proverka_otkrxtiy()
{
		if (!file->isOpened())
		{
	// ������� ���������
			QMessageBox mesBox;
			mesBox.setText("video fail or kamera not available!");
			mesBox.exec();
			file->~VideoCapture();
			en_ds_knopci(true);
			return false;
		}
	
		return true;

}

Face_detection::~Face_detection()
{
	// ����� ������� �������� ����������� �������� ��� ������ ������� ���� �������� ������ � ����.
	// �� ����������� ���������� ������ � ��� ������ ���� ��������� �� ������ �� ����� ����.
	
		haar_cascade->~CascadeClassifier();
		
		if (file)		
			file->~VideoCapture();
		if (qpix)
			qpix->~QPixmap();
		if (time)
			time->~QTimer();
		if (fps_time)
			fps_time->~QTimer();
		if (time_zaderjka)
			delete time_zaderjka;
		
	
}

