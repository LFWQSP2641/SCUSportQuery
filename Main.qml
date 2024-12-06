pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import SCUSportQuery

Window {
    id: sportQueryWindow
    width: 640
    height: 480
    visible: true
    title: qsTr("体育理论题库")

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 5
        spacing: 10
        RowLayout {
            Layout.fillWidth: true
            TextField {
                id: questionTextField
                Layout.fillWidth: true
                placeholderText: "请输入题目"
            }
            Button {
                text: "粘贴"
                onClicked: {
                    questionTextField.paste()
                }
            }
            Button {
                text: "查询"
                onClicked: {
                    sportQueryDBRead.search(questionTextField.text)
                }
            }
        }
        ListView {
            id: questionListView
            Layout.fillWidth: true
            Layout.fillHeight: true
            clip: true
            model: sportQuestionListModel
            delegate: Item {
                id: questionItem
                required property var model
                width: questionListView.width
                height: Math.max(issueText.height, choiceText.height, answerText.height) + 10
                Rectangle {
                    width: parent.width
                    height: parent.height

                    // color: "lightgray"
                    // border.color: "black"
                    border.width: 1
                    RowLayout {
                        anchors.fill: parent
                        spacing: 0
                        Text {
                            id: issueText
                            Layout.alignment: Qt.AlignVCenter
                            Layout.maximumWidth: questionItem.width - choiceText.width - answerText.width
                            Layout.fillWidth: true
                            padding: 5
                            wrapMode: Text.Wrap
                            text: questionItem.model.issue
                        }
                        Text {
                            id: choiceText
                            Layout.alignment: Qt.AlignVCenter
                            padding: 5
                            text: questionItem.model.choice
                        }
                        Text {
                            id: answerText
                            Layout.alignment: Qt.AlignVCenter
                            padding: 5
                            text: questionItem.model.answer
                        }
                    }
                }
            }
        }
    }
    SportQuestionListModel {
        id: sportQuestionListModel
    }
    SportQueryDBRead {
        id: sportQueryDBRead
        onSearchResult: function(searchResult) {
            sportQuestionListModel.receiveSearchResult(searchResult)
        }
    }
}
