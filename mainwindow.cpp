#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHBoxLayout>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QFrame>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setMinimumSize(900, 560);
    setWindowTitle("GameHub");

    // Main widget and layout
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    QHBoxLayout *mainLayout = new QHBoxLayout(central);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Nav panel (far left)
    QWidget *navPanel = new QWidget();
    navPanel->setFixedWidth(52);
    navPanel->setStyleSheet(R"(
        QWidget {
            background-color: #0f0f0f;
        }
        QPushButton {
            background-color: transparent;
            border: none;
            border-radius: 8px;
            padding: 8px;
            color: #666666;
            font-size: 18px;
        }
        QPushButton:hover {
            background-color: #1e1e1e;
            color: #aaaaaa;
        }
        QPushButton:checked {
            background-color: #1e1e1e;
            color: #ffffff;
        }
    )");

    QVBoxLayout *navLayout = new QVBoxLayout(navPanel);
    navLayout->setContentsMargins(8, 12, 8, 12);
    navLayout->setSpacing(8);
    navLayout->setAlignment(Qt::AlignTop);

    QPushButton *libraryBtn = new QPushButton("⊞");
    libraryBtn->setFixedSize(36, 36);
    libraryBtn->setCheckable(true);
    libraryBtn->setChecked(true);

    QPushButton *statsBtn = new QPushButton("▦");
    statsBtn->setFixedSize(36, 36);
    statsBtn->setCheckable(true);

    QWidget *navSpacer = new QWidget();
    navSpacer->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);

    QPushButton *settingsBtn = new QPushButton("⚙");
    settingsBtn->setFixedSize(36, 36);
    settingsBtn->setCheckable(true);

    navLayout->addWidget(libraryBtn);
    navLayout->addWidget(statsBtn);
    navLayout->addWidget(navSpacer);
    navLayout->addWidget(settingsBtn);

    // Sidebar panel (middle)
    QWidget *sidebarPanel = new QWidget();
    sidebarPanel->setFixedWidth(240);
    sidebarPanel->setStyleSheet(R"(
        QWidget {
            background-color: #111111;
        }
        QLineEdit {
            background-color: #0f0f0f;
            border: 1px solid #2a2a2a;
            border-radius: 8px;
            padding: 6px 10px;
            color: #aaaaaa;
            font-size: 12px;
        }
        QLabel#sectionLabel {
            color: #555555;
            font-size: 11px;
        }
    )");

    QVBoxLayout *sidebarLayout = new QVBoxLayout(sidebarPanel);
    sidebarLayout->setContentsMargins(0, 0, 0, 0);
    sidebarLayout->setSpacing(0);

    // Header label
    QLabel *libraryLabel = new QLabel("LIBRARY");
    libraryLabel->setObjectName("sectionLabel");
    libraryLabel->setContentsMargins(14, 14, 14, 8);

    // Search bar
    QLineEdit *searchBar = new QLineEdit();
    searchBar->setPlaceholderText("Search games...");
    searchBar->setContentsMargins(10, 0, 10, 10);
    QWidget *searchWrapper = new QWidget();
    QVBoxLayout *searchLayout = new QVBoxLayout(searchWrapper);
    searchLayout->setContentsMargins(10, 0, 10, 10);
    searchLayout->addWidget(searchBar);

    // Scroll area for game grid
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setStyleSheet(R"(
        QScrollArea {
            border: none;
            background-color: transparent;
        }
        QScrollBar:vertical {
            width: 4px;
            background: transparent;
        }
        QScrollBar::handle:vertical {
            background: #2a2a2a;
            border-radius: 2px;
        }
    )");

    QWidget *gridContainer = new QWidget();
    gridContainer->setStyleSheet("background-color: #111111;");
    QGridLayout *gameGrid = new QGridLayout(gridContainer);
    gameGrid->setContentsMargins(8, 8, 8, 8);
    gameGrid->setSpacing(8);

    // Placeholder game cards
    QStringList games = {"Elden Ring", "Dark Souls III", "Hollow Knight", "Cyberpunk 2077", "Hades", "RimWorld"};
    QStringList times = {"142h", "89h", "34h", "67h", "21h", "210h"};
    QStringList colors = {"#1a2a3a", "#2a1a1a", "#1a2a1a", "#2a2a1a", "#2a1a2a", "#1a1a2a"};

    for (int i = 0; i < games.size(); i++) {
        QWidget *card = new QWidget();
        card->setStyleSheet(QString(R"(
            QWidget {
                background-color: #1a1a1a;
                border: 1px solid #2a2a2a;
                border-radius: 8px;
            }
            QWidget:hover {
                border: 1px solid #3a3a3a;
            }
        )"));
        card->setCursor(Qt::PointingHandCursor);

        QVBoxLayout *cardLayout = new QVBoxLayout(card);
        cardLayout->setContentsMargins(0, 0, 0, 0);
        cardLayout->setSpacing(0);

        // Thumbnail
        QLabel *thumb = new QLabel();
        thumb->setFixedHeight(60);
        thumb->setStyleSheet(QString("background-color: %1; border-radius: 8px 8px 0px 0px;").arg(colors[i]));

        // Game name
        QLabel *nameLabel = new QLabel(games[i]);
        nameLabel->setStyleSheet("color: #cccccc; font-size: 11px; padding: 5px 7px 2px 7px; border: none;");

        // Playtime
        QLabel *timeLabel = new QLabel(times[i] + " played");
        timeLabel->setStyleSheet("color: #555555; font-size: 10px; padding: 0px 7px 5px 7px; border: none;");

        cardLayout->addWidget(thumb);
        cardLayout->addWidget(nameLabel);
        cardLayout->addWidget(timeLabel);

        gameGrid->addWidget(card, i / 2, i % 2);
    }

    scrollArea->setWidget(gridContainer);

    sidebarLayout->addWidget(libraryLabel);
    sidebarLayout->addWidget(searchWrapper);
    sidebarLayout->addWidget(scrollArea);

    // Detail panel (right)
    QWidget *detailPanel = new QWidget();
    detailPanel->setStyleSheet("background-color: #141414;");

    QVBoxLayout *detailLayout = new QVBoxLayout(detailPanel);
    detailLayout->setContentsMargins(0, 0, 0, 0);
    detailLayout->setSpacing(0);

    // Hero area
    QWidget *heroWidget = new QWidget();
    heroWidget->setFixedHeight(180);
    heroWidget->setStyleSheet("background-color: #1a2a3a;");

    QVBoxLayout *heroLayout = new QVBoxLayout(heroWidget);
    heroLayout->setContentsMargins(16, 0, 16, 16);
    heroLayout->setAlignment(Qt::AlignBottom);

    QLabel *gameTitleLabel = new QLabel("Elden Ring");
    gameTitleLabel->setStyleSheet("color: #ffffff; font-size: 22px; font-weight: 500; background: transparent;");
    heroLayout->addWidget(gameTitleLabel);

    // Body area
    QWidget *bodyWidget = new QWidget();
    bodyWidget->setStyleSheet("background-color: #141414;");

    QVBoxLayout *bodyLayout = new QVBoxLayout(bodyWidget);
    bodyLayout->setContentsMargins(16, 16, 16, 16);
    bodyLayout->setSpacing(14);
    bodyLayout->setAlignment(Qt::AlignTop);

    // Stats row
    QWidget *statsRow = new QWidget();
    statsRow->setStyleSheet("background: transparent;");
    QHBoxLayout *statsLayout = new QHBoxLayout(statsRow);
    statsLayout->setContentsMargins(0, 0, 0, 0);
    statsLayout->setSpacing(10);

    auto makeStatBox = [](const QString &label, const QString &value) -> QWidget* {
        QWidget *box = new QWidget();
        box->setStyleSheet(R"(
            QWidget {
                background-color: #1a1a1a;
                border: 1px solid #2a2a2a;
                border-radius: 8px;
            }
        )");
        QVBoxLayout *layout = new QVBoxLayout(box);
        layout->setContentsMargins(12, 10, 12, 10);
        layout->setSpacing(4);

        QLabel *labelWidget = new QLabel(label.toUpper());
        labelWidget->setStyleSheet("color: #555555; font-size: 10px; border: none; background: transparent;");

        QLabel *valueWidget = new QLabel(value);
        valueWidget->setStyleSheet("color: #eeeeee; font-size: 16px; font-weight: 500; border: none; background: transparent;");

        layout->addWidget(labelWidget);
        layout->addWidget(valueWidget);
        return box;
    };

    statsLayout->addWidget(makeStatBox("Total playtime", "142h 14m"));
    statsLayout->addWidget(makeStatBox("Last played", "2 days ago"));
    statsLayout->addWidget(makeStatBox("Sessions", "47"));

    // Launch button
    QPushButton *launchBtn = new QPushButton("▶  Launch game");
    launchBtn->setFixedHeight(36);
    launchBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #1a6b3c;
            color: #ffffff;
            border: none;
            border-radius: 8px;
            font-size: 13px;
            font-weight: 500;
            padding: 0 20px;
        }
        QPushButton:hover {
            background-color: #1d7d47;
        }
    )");
    launchBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    launchBtn->adjustSize();

    // Recent sessions
    QLabel *sessionsLabel = new QLabel("RECENT SESSIONS");
    sessionsLabel->setStyleSheet("color: #555555; font-size: 10px; background: transparent;");

    QWidget *sessionsList = new QWidget();
    sessionsList->setStyleSheet("background: transparent;");
    QVBoxLayout *sessionsLayout = new QVBoxLayout(sessionsList);
    sessionsLayout->setContentsMargins(0, 0, 0, 0);
    sessionsLayout->setSpacing(4);

    auto makeSessionRow = [](const QString &date, const QString &duration) -> QWidget* {
        QWidget *row = new QWidget();
        row->setStyleSheet(R"(
            QWidget {
                background-color: #1a1a1a;
                border: 1px solid #222222;
                border-radius: 6px;
            }
        )");
        QHBoxLayout *layout = new QHBoxLayout(row);
        layout->setContentsMargins(10, 6, 10, 6);

        QLabel *dateLabel = new QLabel(date);
        dateLabel->setStyleSheet("color: #888888; font-size: 12px; border: none; background: transparent;");

        QLabel *durationLabel = new QLabel(duration);
        durationLabel->setStyleSheet("color: #aaaaaa; font-size: 12px; border: none; background: transparent;");

        layout->addWidget(dateLabel);
        layout->addStretch();
        layout->addWidget(durationLabel);
        return row;
    };

    sessionsLayout->addWidget(makeSessionRow("Today", "2h 14m"));
    sessionsLayout->addWidget(makeSessionRow("Apr 19", "1h 43m"));
    sessionsLayout->addWidget(makeSessionRow("Apr 17", "3h 02m"));

    bodyLayout->addWidget(statsRow);
    bodyLayout->addWidget(launchBtn);
    bodyLayout->addWidget(sessionsLabel);
    bodyLayout->addWidget(sessionsList);
    bodyLayout->addStretch();

    detailLayout->addWidget(heroWidget);
    detailLayout->addWidget(bodyWidget);

    mainLayout->addWidget(navPanel);
    mainLayout->addWidget(sidebarPanel);
    mainLayout->addWidget(detailPanel);
}

MainWindow::~MainWindow()
{
    delete ui;
}