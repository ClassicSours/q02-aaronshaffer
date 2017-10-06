/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"
 
class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor) 
};

TEST(PiezasTest, sanityCheck)
{
	ASSERT_TRUE(true);
}

TEST(PiezasTest, Piezas)
{
	Piezas piezas;
	 for(int i = 0; i < BOARD_ROWS; i++) {
        for(int j = 0; j < BOARD_COLS; j++) {
			ASSERT_EQ(piezas.pieceAt(i,j),Blank);
        }
    }
}

TEST(PiezasTest, PiezasReset)
{
	Piezas piezas;
	piezas.reset();
	for(int i = 0; i < BOARD_ROWS; i++) {
    	for(int j = 0; j < BOARD_COLS; j++) {
			ASSERT_EQ(piezas.pieceAt(i,j),Blank);
        }
    }
}

TEST(PiezasTest, resetClearsBoard) {
	Piezas piezas;
	
	for(int i = 0; i < BOARD_ROWS; i++) {
    	for(int j = 0; j < BOARD_COLS; j++) {
    		piezas.dropPiece(j);
	    }
    }
	
	piezas.reset();
	
	for(int i = 0; i < BOARD_ROWS; i++) {
    	for(int j = 0; j < BOARD_COLS; j++) {
			ASSERT_EQ(piezas.pieceAt(i,j),Blank);
        }
    }
}

TEST(PiezasTest, gameStateAfterResetisInvalid) {
	Piezas piezas;
	
	for(int i = 0; i < BOARD_ROWS; i++) {
    	for(int j = 0; j < BOARD_COLS; j++) {
    		piezas.dropPiece(j);
	    }
    }
	
	piezas.reset();
	
	ASSERT_EQ(piezas.gameState(),Invalid);
}


TEST(PiezasTest, InvalidGameStateAtStart) {
	Piezas piezas;
	ASSERT_EQ(piezas.gameState(),Invalid);
}

TEST(PiezasTest, DropPieceX0isX) {
	Piezas piezas;
	ASSERT_EQ(piezas.dropPiece(0),X);
}

TEST(PiezasTest, DropPieceX0) {
	Piezas piezas;
	piezas.dropPiece(0);
	ASSERT_EQ(piezas.pieceAt(0,0),X);
}

TEST(PiezasTest, DropPieceChangesTurns) {
	Piezas piezas;
	piezas.dropPiece(0);
	ASSERT_EQ(piezas.dropPiece(0),O);
}

TEST(PiezasTest, DropPieceX0O0) {
	Piezas piezas;
	piezas.dropPiece(0);
	piezas.dropPiece(0);
	ASSERT_EQ(piezas.pieceAt(1,0),O);
}

TEST(PiezasTest, DropEverwhere) {
	Piezas piezas;
	for(int i = 0; i < BOARD_ROWS; i++) {
    	for(int j = 0; j < BOARD_COLS; j++) {
			piezas.dropPiece(j);
        }
    }
    ASSERT_EQ(piezas.gameState(),Blank);
}

TEST(PiezasTest, XWin) {
	Piezas piezas;
	piezas.dropPiece(0);
	piezas.dropPiece(0);
	piezas.dropPiece(1);
	piezas.dropPiece(1);
	
	piezas.dropPiece(2);
	piezas.dropPiece(2);
	piezas.dropPiece(3);
	piezas.dropPiece(0);
	
	piezas.dropPiece(3);
	piezas.dropPiece(1);
	piezas.dropPiece(2);
	piezas.dropPiece(3);
	
    ASSERT_EQ(piezas.gameState(),X);
}

TEST(PiezasTest, OWin) {
	Piezas piezas;
	piezas.dropPiece(0);
	piezas.dropPiece(0);
	piezas.dropPiece(1);
	piezas.dropPiece(1);
	
	piezas.dropPiece(2);
	piezas.dropPiece(2);
	piezas.dropPiece(0);
	piezas.dropPiece(3);
	
	piezas.dropPiece(1);
	piezas.dropPiece(3);
	piezas.dropPiece(3);
	piezas.dropPiece(2);
	
    ASSERT_EQ(piezas.gameState(),O);
}

TEST(PiezasTest, gameIsntOver) {
	Piezas piezas;
	
	piezas.dropPiece(0);
	piezas.dropPiece(0);
	piezas.dropPiece(1);
	piezas.dropPiece(1);
	
	piezas.dropPiece(2);
	piezas.dropPiece(2);
	piezas.dropPiece(0);
	piezas.dropPiece(3);
	
	piezas.dropPiece(3);
	piezas.dropPiece(1);
	piezas.dropPiece(3);
	
	ASSERT_EQ(piezas.gameState(),Invalid);
}

TEST(PiezasTest, gameIsTieHorizontal) {
	Piezas piezas;
	
	piezas.dropPiece(0);
	piezas.dropPiece(0);
	piezas.dropPiece(1);
	piezas.dropPiece(1);
	
	piezas.dropPiece(2);
	piezas.dropPiece(2);
	piezas.dropPiece(3);
	piezas.dropPiece(3);
	
	piezas.dropPiece(0);
	piezas.dropPiece(1);
	piezas.dropPiece(2);
	piezas.dropPiece(3);
	
	ASSERT_EQ(piezas.gameState(), Blank);
}

TEST(PiezasTest, gameIsTieCheckerboard) {
	Piezas piezas;
	
	piezas.dropPiece(0);
	piezas.dropPiece(1);
	piezas.dropPiece(2);
	piezas.dropPiece(3);
	
	piezas.dropPiece(3);
	piezas.dropPiece(2);
	piezas.dropPiece(1);
	piezas.dropPiece(0);
	
	piezas.dropPiece(0);
	piezas.dropPiece(1);
	piezas.dropPiece(2);
	piezas.dropPiece(3);
	
	ASSERT_EQ(piezas.gameState(), Blank);
}

TEST(PiezasTest, XWinVertical) {
	Piezas piezas;
	
	piezas.dropPiece(0);
	piezas.dropPiece(1);
	piezas.dropPiece(2);
	piezas.dropPiece(3);
	
	piezas.dropPiece(0);
	piezas.dropPiece(2);
	piezas.dropPiece(0);
	piezas.dropPiece(2);
	
	piezas.dropPiece(1);
	piezas.dropPiece(3);
	piezas.dropPiece(3);
	piezas.dropPiece(1);
	
	ASSERT_EQ(piezas.gameState(), X);
}

TEST(PiezasTest, OWinVertical) {
	Piezas piezas;
	
	piezas.dropPiece(3);
	piezas.dropPiece(2);
	piezas.dropPiece(1);
	piezas.dropPiece(0);
	
	piezas.dropPiece(0);
	piezas.dropPiece(2);
	piezas.dropPiece(0);
	piezas.dropPiece(2);
	
	piezas.dropPiece(1);
	piezas.dropPiece(3);
	piezas.dropPiece(3);
	piezas.dropPiece(1);
	
	ASSERT_EQ(piezas.gameState(), O);
}

TEST(PiezasTest, allXisXwin) {
	Piezas piezas;
	
	for(int i = 0; i < BOARD_ROWS; i++) {
		for(int j = 0; j < BOARD_COLS; j++) {
			piezas.dropPiece(j);
			piezas.dropPiece(-1);
		}
	}
	ASSERT_EQ(piezas.gameState(),X);
}

TEST(PiezasTest, allOisOwin) {
	Piezas piezas;
	
	for(int i = 0; i < BOARD_ROWS; i++) {
		for(int j = 0; j < BOARD_COLS; j++) {
			piezas.dropPiece(-1);
			piezas.dropPiece(j);
		}
	}
	ASSERT_EQ(piezas.gameState(),O);
}

TEST(PiezasTest, dropOOBNeg) {
	Piezas piezas;
	ASSERT_EQ(piezas.dropPiece(-1),Invalid);
}

TEST(PiezasTest, dropOOBNegChangesTurn) {
	Piezas piezas;
	
	piezas.dropPiece(-1);
	ASSERT_EQ(piezas.dropPiece(0),O);
}

TEST(PiezasTest, dropOOBPos) {
	Piezas piezas;
	ASSERT_EQ(piezas.dropPiece(4),Invalid);
}

TEST(PiezasTest, dropOOBPosChangesTurn) {
	Piezas piezas;
	
	piezas.dropPiece(4);
	ASSERT_EQ(piezas.dropPiece(0),O);
}

TEST(PiezasTest, dropOnFUllColumn0isBlank) {
	Piezas piezas;
	
	for(int i = 0; i < BOARD_ROWS; i++) {
		piezas.dropPiece(0);
	}
	ASSERT_EQ(piezas.dropPiece(0),Blank);
}

TEST(PiezasTest, dropOnFUllColumn1isBlank) {
	Piezas piezas;
	
	for(int i = 0; i < BOARD_ROWS; i++) {
		piezas.dropPiece(1);
	}
	ASSERT_EQ(piezas.dropPiece(1),Blank);
}

TEST(PiezasTest, dropOnFUllColumn2isBlank) {
	Piezas piezas;
	
	for(int i = 0; i < BOARD_ROWS; i++) {
		piezas.dropPiece(2);
	}
	ASSERT_EQ(piezas.dropPiece(2),Blank);
}

TEST(PiezasTest, dropOnFUllColumn3isBlank) {
	Piezas piezas;
	
	for(int i = 0; i < BOARD_ROWS; i++) {
		piezas.dropPiece(3);
	}
	ASSERT_EQ(piezas.dropPiece(3),Blank);
}

TEST(PiezasTest, longintOverflowIs0) {
	Piezas piezas;
	long int test = 0x16ffffff00000000L;
	ASSERT_EQ(piezas.dropPiece(test),X);
}

TEST(PiezasTest, pieceAtBlank) {
	Piezas piezas;
	ASSERT_EQ(piezas.pieceAt(0,0),Blank);
}

TEST(PiezasTest, pieceAtInvalidNegValid) {
	Piezas piezas;
	ASSERT_EQ(piezas.pieceAt(-1,0),Invalid);
}


TEST(PiezasTest, pieceAtValidInvalidNeg) {
	Piezas piezas;
	ASSERT_EQ(piezas.pieceAt(0,-1),Invalid);
}

TEST(PiezasTest, pieceAtInvalidNegInvalidNeg) {
	Piezas piezas;
	ASSERT_EQ(piezas.pieceAt(-1,-1),Invalid);
}

TEST(PiezasTest, pieceAtInvalidPosValid) {
	Piezas piezas;
	ASSERT_EQ(piezas.pieceAt(BOARD_ROWS,0),Invalid);
}


TEST(PiezasTest, pieceAtValidInvalidPos) {
	Piezas piezas;
	ASSERT_EQ(piezas.pieceAt(0,BOARD_COLS),Invalid);
}

TEST(PiezasTest, pieceAtInvalidPosInvalidPos) {
	Piezas piezas;
	ASSERT_EQ(piezas.pieceAt(BOARD_ROWS,BOARD_COLS),Invalid);
}

TEST(PiezasTest, pieceAtIsX) {
	Piezas piezas;
	
	for(int i = 0; i < BOARD_ROWS; i++) {
		for(int j = 0; j < BOARD_COLS; j++) {
			piezas.dropPiece(j);
			piezas.dropPiece(-1);
			ASSERT_EQ(piezas.pieceAt(i,j),X);
		}
	}
}

TEST(PiezasTest, pieceAtIsO) {
	Piezas piezas;
	
	for(int i = 0; i < BOARD_ROWS; i++) {
		for(int j = 0; j < BOARD_COLS; j++) {
			piezas.dropPiece(-1);
			piezas.dropPiece(j);
			ASSERT_EQ(piezas.pieceAt(i,j),O);
		}
	}
}

