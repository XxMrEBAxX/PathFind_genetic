#pragma once

struct POSITION
{
	int X;
	int Y;

	POSITION(int x, int y) : X(x), Y(y) {}
	POSITION() : X(0), Y(0) {}

	// ���� Ʈ������ Ž���� �� �־�� �ϹǷ� �߰� ( map ���� key ������ ���� ���� )
	bool operator<(const POSITION& rhs) const noexcept
	{
		// logic here
		if (X != rhs.X)
		{
			return X < rhs.X;
		}
		return this->Y < rhs.Y;
	}
	bool operator!=(const POSITION& rhs) const noexcept
	{
		return X != rhs.X || this->Y != rhs.Y;
	}
	bool operator==(const POSITION& rhs) const noexcept
	{
		return X == rhs.X && this->Y == rhs.Y;
	}
	POSITION operator-(const POSITION& rhs) const noexcept
	{
		return POSITION(X - rhs.X, this->Y - rhs.Y);
	}
};