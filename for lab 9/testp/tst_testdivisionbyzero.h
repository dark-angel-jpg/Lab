#ifndef TST_TESTDIVISIONBYZERO_H
#define TST_TESTDIVISIONBYZERO_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <IKeypad.h>
#include <ILatch.h>
#include <lockcontroller.h>

using namespace testing;

struct MockKey : IKeypad {
    MOCK_METHOD(
            bool,
            isActive,
            (),
            (override));

    MOCK_METHOD(
            void,
            wait,
            (),
            (override));

    MOCK_METHOD(
            PasswordResponse,
            requestPassword,
            (),
            (override));
};

struct MockLat : ILatch {
    MOCK_METHOD(
            bool,
            isActive,
            (),
            (override));

    MOCK_METHOD(
            DoorStatus,
            open,
            (),
            (override));

    MOCK_METHOD(
            DoorStatus,
            close,
            (),
            (override));

    MOCK_METHOD(
            DoorStatus,
            getDoorStatus,
            (),
            (override));
};

TEST(LockControllerSuite, test1){
    //Arrange
    MockKey MK;
    MockLat ML;
    LockController LC(&MK, &ML);
    EXPECT_CALL(MK, wait())
            .Times(1)
            .WillOnce(Return());
    //Act
    LC.wait();
    //Assert
}

TEST(LockControllerSuite, test2){
    //Arrange
    MockKey MK;
    MockLat ML;
    LockController LC(&MK, &ML);
    EXPECT_CALL(ML, getDoorStatus())
            .Times(1)
            .WillOnce(Return(DoorStatus::CLOSE));
    //Act
    bool r = LC.isDoorOpen();
    //Assert
    EXPECT_FALSE(r);
}

TEST(LockControllerSuite, test3){
    //Arrange
    MockKey MK;
    MockLat ML;
    LockController LC(&MK, &ML);
    EXPECT_CALL(ML, getDoorStatus())
            .Times(1)
            .WillOnce(Return(DoorStatus::OPEN));
    //Act
    bool r = LC.isDoorOpen();
    //Assert
    EXPECT_TRUE(r);
}

TEST(LockControllerSuite, test4){
    //Arrange
    MockKey MK;
    MockLat ML;
    LockController LC(&MK, &ML);
    EXPECT_CALL(ML, open())
            .Times(1)
            .WillOnce(Return(DoorStatus::OPEN));
    //Act
    DoorStatus r = LC.unlockDoor();
    //Assert
    EXPECT_EQ(r, DoorStatus::OPEN);
}

TEST(LockControllerSuite, test5){
    //Arrange
    MockKey MK;
    MockLat ML;
    LockController LC(&MK, &ML);
    EXPECT_CALL(ML, close())
            .Times(1)
            .WillOnce(Return(DoorStatus::CLOSE));
    //Act
    DoorStatus r = LC.lockDoor();
    //Assert
    EXPECT_EQ(r, DoorStatus::CLOSE);
}

TEST(LockControllerSuite, test6){
    //Arrange
    MockKey MK;
    MockLat ML;
    LockController LC(&MK, &ML);
    EXPECT_CALL(MK, isActive())
            .Times(1)
            .WillOnce(Return(1));
    EXPECT_CALL(ML, isActive)
            .Times(1)
            .WillOnce(Return(1));
    //Act
    HardWareStatus r = LC.hardWareCheck();
    //Assert
    EXPECT_EQ(r, HardWareStatus::OK);
}

TEST(LockControllerSuite, test7){
    //Arrange
    MockKey MK;
    MockLat ML;
    LockController LC(nullptr, &ML);
    EXPECT_CALL(MK, isActive())
            .Times(AtLeast(0))
            .WillOnce(Return(0));
    EXPECT_CALL(ML, isActive)
            .Times(AtLeast(0))
            .WillOnce(Return(1));
    //Act
    HardWareStatus r = LC.hardWareCheck();
    //Assert
    EXPECT_EQ(r, HardWareStatus::ERROR);
}

TEST(LockControllerSuite, test8){
    //Arrange
    MockKey MK;
    MockLat ML;
    LockController LC(&MK, &ML);
    EXPECT_CALL(MK, isActive())
            .Times(1)
            .WillOnce(Return(1));
    EXPECT_CALL(ML, isActive)
            .Times(1)
            .WillOnce(Return(0));
    //Act
    HardWareStatus r = LC.hardWareCheck();
    //Assert
    EXPECT_EQ(r, HardWareStatus::ERROR);
}

TEST(LockControllerSuite, test9){
    //Arrange
    MockKey MK;
    MockLat ML;
    LockController LC(&MK, &ML);
    PasswordResponse P {PasswordResponse::Status::OK, "0000"};
    EXPECT_CALL(MK, requestPassword())
            .Times(1)
            .WillOnce(Return(P));
    //Act
    bool r = LC.isCorrectPassword();
    //Assert
    EXPECT_TRUE(r);
}

TEST(LockControllerSuite, test10){
    //Arrange
    MockKey MK;
    MockLat ML;
    LockController LC(&MK, &ML);
    PasswordResponse P {PasswordResponse::Status::OK, "1010"};
    EXPECT_CALL(MK, requestPassword())
            .Times(1)
            .WillOnce(Return(P));
    //Act
    bool r = LC.isCorrectPassword();
    //Assert
    EXPECT_FALSE(r);
}

TEST(LockControllerSuite, test11){
    //Arrange
    MockKey MK;
    MockLat ML;
    LockController LC(&MK, &ML);
    PasswordResponse P1 {PasswordResponse::Status::OK, "0000"};
    PasswordResponse P2 {PasswordResponse::Status::OK, "0101"};
    PasswordResponse P3 {PasswordResponse::Status::OK, "0101"};
    EXPECT_CALL(MK, requestPassword())
            .Times(3)
            .WillOnce(Return(P1))
            .WillOnce(Return(P2))
            .WillOnce(Return(P3));
    //Act
    LC.resetPassword();
    bool r = LC.isCorrectPassword();
    //Assert
    EXPECT_TRUE(r);
}

TEST(LockControllerSuite, test12){
    //Arrange
    MockKey MK;
    MockLat ML;
    LockController LC(&MK, &ML);
    PasswordResponse P1 {PasswordResponse::Status::OK, "0000"};
    PasswordResponse P2 {PasswordResponse::Status::OK, "9876"};
    PasswordResponse P3 {PasswordResponse::Status::OK, "9876"};
    PasswordResponse P4 {PasswordResponse::Status::OK, "2520"};
    PasswordResponse P5 {PasswordResponse::Status::OK, "2520"};
    EXPECT_CALL(MK, requestPassword())
            .Times(5)
            .WillOnce(Return(P1))
            .WillOnce(Return(P2))
            .WillOnce(Return(P3))
            .WillOnce(Return(P4))
            .WillOnce(Return(P5));
    //Act
    LC.resetPassword();
    LC.resetPassword();
    bool r = LC.isCorrectPassword();
    //Assert
    EXPECT_TRUE(r);
}

#endif
