# -*- coding: utf-8 -*-
"""
Created on Tue Nov 25 11:32:19 2025

@author: 多墨云
"""

import pygame
import random
import sys
from pygame.locals import *

# 初始化pygame
pygame.init()

# 游戏设置
WIDTH, HEIGHT = 800, 600
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("连连看小游戏")

# 强制获取键盘焦点
pygame.event.set_grab(True)

# 颜色定义
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GRAY = (200, 200, 200)
BLUE = (0, 0, 255)
RED = (255, 0, 0)
GREEN = (0, 255, 0)

# 字体设置
try:
    font = pygame.font.SysFont(["SimHei", "Microsoft YaHei", "Arial"], 40)
    small_font = pygame.font.SysFont(["SimHei", "Microsoft YaHei", "Arial"], 30)
except:
    font = pygame.font.Font(None, 40)
    small_font = pygame.font.Font(None, 30)

# 关卡配置
levels = {
    1: {"rows": 4, "cols": 4, "time": 60},
    2: {"rows": 5, "cols": 6, "time": 80},
    3: {"rows": 6, "cols": 8, "time": 100},
    4: {"rows": 7, "cols": 9, "time": 120},
}

# 方块类
class Block:
    def __init__(self, x, y, image_num):
        self.x = x
        self.y = y
        self.image_num = image_num
        self.selected = False
        self.visible = True
        self.rect = pygame.Rect(x, y, 60, 60)

    def draw(self):
        if self.visible:
            color = GRAY if not self.selected else BLUE
            pygame.draw.rect(screen, color, self.rect, 2)
            colors = [RED, GREEN, BLUE, (255, 255, 0), (255, 165, 0), 
                      (128, 0, 128), (0, 255, 255), (0, 128, 0)]
            pygame.draw.circle(screen, colors[self.image_num % len(colors)], 
                               (self.x + 30, self.y + 30), 25)

# 游戏类
class LinkGame:
    def __init__(self):
        self.level = 1
        self.reset_game()

    def reset_game(self):
        config = levels[self.level]
        self.rows = config["rows"]
        self.cols = config["cols"]
        self.time_left = config["time"]
        self.score = 0
        self.blocks = []
        self.selected_block = None
        self.game_over = False
        self.win = False
        self.create_blocks()
        self.last_time_update = pygame.time.get_ticks()

    def create_blocks(self):
        total_blocks = self.rows * self.cols
        if total_blocks % 2 != 0:
            total_blocks += 1
        image_nums = list(range(total_blocks // 2)) * 2
        random.shuffle(image_nums)

        start_x = (WIDTH - self.cols * 70) // 2
        start_y = 100

        self.blocks = []
        for i in range(self.rows):
            row = []
            for j in range(self.cols):
                x = start_x + j * 70
                y = start_y + i * 70
                idx = i * self.cols + j
                image_num = image_nums[idx] if idx < len(image_nums) else 0
                block = Block(x, y, image_num)
                row.append(block)
            self.blocks.append(row)

    def check_connection(self, block1, block2):
        if block1.image_num != block2.image_num or not block1.visible or not block2.visible:
            return False

        if block1.x == block2.x or block1.y == block2.y:
            if self.check_line(block1, block2):
                return True

        if self.check_corner(block1, block2):
            return True

        return False

    def check_line(self, block1, block2):
        min_x, max_x = min(block1.x, block2.x), max(block1.x, block2.x)
        min_y, max_y = min(block1.y, block2.y), max(block1.y, block2.y)

        if block1.x == block2.x:
            for i in range(self.rows):
                for j in range(self.cols):
                    block = self.blocks[i][j]
                    if (block.x == block1.x and min_y < block.y < max_y and 
                        block.visible and block != block1 and block != block2):
                        return False
        else:
            for i in range(self.rows):
                for j in range(self.cols):
                    block = self.blocks[i][j]
                    if (block.y == block1.y and min_x < block.x < max_x and 
                        block.visible and block != block1 and block != block2):
                        return False
        return True

    def check_corner(self, block1, block2):
        corner1 = Block(block1.x, block2.y, -1)
        if self.check_line(block1, corner1) and self.check_line(corner1, block2):
            return True

        corner2 = Block(block2.x, block1.y, -1)
        if self.check_line(block1, corner2) and self.check_line(corner2, block2):
            return True

        return False

    def check_win(self):
        for row in self.blocks:
            for block in row:
                if block.visible:
                    return False
        return True

    def draw(self):
        screen.fill(WHITE)

        title_text = font.render(f"连连看 - 关卡 {self.level}", True, BLACK)
        screen.blit(title_text, (WIDTH // 2 - title_text.get_width() // 2, 20))

        score_text = small_font.render(f"得分: {self.score}", True, BLACK)
        screen.blit(score_text, (20, 20))

        time_text = small_font.render(f"时间: {int(self.time_left)}", True, 
                                     RED if self.time_left < 10 else BLACK)
        screen.blit(time_text, (WIDTH - 120, 20))

        for row in self.blocks:
            for block in row:
                block.draw()

        if self.game_over:
            overlay = pygame.Surface((WIDTH, HEIGHT), pygame.SRCALPHA)
            overlay.fill((0, 0, 0, 180))
            screen.blit(overlay, (0, 0))

            if self.win:
                if self.level < len(levels):
                    msg_lines = [
                        f"恭喜通关！得分: {self.score}",
                        f"当前关卡: {self.level} -> 下一关: {self.level + 1}",
                        "按 N 键进入下一关",
                        "按 R 键重新开始"
                    ]
                else:
                    msg_lines = [
                        "🎉 恭喜通关所有关卡！🎉",
                        f"最终得分: {self.score}",
                        "按 R 键重新开始游戏"
                    ]
            else:
                msg_lines = [
                    "游戏结束！时间已用完",
                    f"最终得分: {self.score}",
                    "按 R 键重新开始"
                ]

            y_offset = HEIGHT // 2 - len(msg_lines) * 25
            for line in msg_lines:
                line_text = font.render(line, True, WHITE)
                screen.blit(line_text, (WIDTH // 2 - line_text.get_width() // 2, y_offset))
                y_offset += 45

        pygame.display.update()

    def handle_click(self, pos):
        if self.game_over:
            return

        for row in self.blocks:
            for block in row:
                if block.rect.collidepoint(pos) and block.visible:
                    if self.selected_block is None:
                        self.selected_block = block
                        block.selected = True
                    else:
                        if block == self.selected_block:
                            self.selected_block.selected = False
                            self.selected_block = None
                        else:
                            if self.check_connection(self.selected_block, block):
                                self.selected_block.visible = False
                                block.visible = False
                                self.score += 10
                                self.selected_block.selected = False
                                self.selected_block = None

                                if self.check_win():
                                    self.game_over = True
                                    self.win = True
                            else:
                                self.selected_block.selected = False
                                self.selected_block = None
                    return

    def update(self):
        if not self.game_over and self.time_left > 0:
            current_time = pygame.time.get_ticks()
            if current_time - self.last_time_update >= 1000:
                self.time_left -= 1
                self.last_time_update = current_time
            if self.time_left <= 0:
                self.game_over = True
                self.win = False

    def handle_key(self, key):
        """独立的按键处理函数"""
        if self.game_over:
            if key == K_r:
                self.restart()
            elif key == K_n and self.win and self.level < len(levels):
                self.next_level()
                return True
        return False

    def next_level(self):
        if self.level < len(levels):
            self.level += 1
            self.reset_game()

    def restart(self):
        self.level = 1  # 重新开始时回到第一关
        self.reset_game()

# 主函数
def main():
    game = LinkGame()
    clock = pygame.time.Clock()

    running = True
    while running:
        for event in pygame.event.get():
            if event.type == QUIT:
                running = False
            elif event.type == MOUSEBUTTONDOWN:
                if event.button == 1:
                    game.handle_click(pygame.mouse.get_pos())
            elif event.type == KEYDOWN:
                # 所有按键都在这里处理
                if event.key == K_ESCAPE:
                    running = False
                # 调用游戏的按键处理
                game.handle_key(event.key)
                
                # 调试：打印按键信息
                print(f"按键: {pygame.key.name(event.key)}")

        game.update()
        game.draw()
        clock.tick(60)

    pygame.quit()
    sys.exit()

if __name__ == "__main__":
    main()