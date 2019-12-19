#pragma once

using ScoreT = unsigned;

class Score {
  ScoreT current = 0;

 public:
  void setCurrentScore(ScoreT newScore);
  ScoreT getCurrentScore() const;

  void reset();

  void addPointsForGift();
  void addPointsForHeight();
  void addPointsForTimeLeft(byte secondsLeft);
  void addPointsForLivesLeft(byte livesLeft);

  bool isHighScore() const;
  void updateHighScoreList();
};

extern Score score;
