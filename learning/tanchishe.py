import pygame
import random
import sys

# 初始化pygame
try:
    pygame.init()
except pygame.error as e:
    print(f"Pygame 初始化失败: {e}")
    sys.exit()

# 设置窗口大小
width, height = 800, 800
window = pygame.display.set_mode((width, height))
pygame.display.set_caption("贪吃蛇游戏")

# 定义颜色
white = (255, 255, 255)
black = (0, 0, 0)
red = (213, 50, 80)
green = (0, 255, 0)

# 蛇和食物的初始设置
snake_block_size = 20
snake_speed = 5

font_style = pygame.font.SysFont(None, 50)

def our_snake(snake_block, snake_list):
    for x in snake_list:
        pygame.draw.rect(window, black, [x[0], x[1], snake_block, snake_block])

def message(msg, color):
    mesg = font_style.render(msg, True, color)
    window.blit(mesg, [width / 6, height / 3])

def gameLoop():
    game_over = False
    game_close = False

    x1 = width // 2
    y1 = height // 2

    x1_change = 0       
    y1_change = 0

    snake_List = []
    Length_of_snake = 1

    foodx = round(random.randrange(0, width - snake_block_size) / 20.0) * 20.0
    foody = round(random.randrange(0, height - snake_block_size) / 20.0) * 20.0

    clock = pygame.time.Clock()

    while not game_over:

        while game_close:
            window.fill(white)
            message("You Lost! Press Q-Quit or C-Play Again", red)
            pygame.display.update()

            for event in pygame.event.get():
                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_q:
                        game_over = True
                        game_close = False
                    elif event.key == pygame.K_c:
                        gameLoop()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                game_over = True
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_LEFT:
                    x1_change = -snake_block_size
                    y1_change = 0
                elif event.key == pygame.K_RIGHT:
                    x1_change = snake_block_size
                    y1_change = 0
                elif event.key == pygame.K_UP:
                    y1_change = -snake_block_size
                    x1_change = 0
                elif event.key == pygame.K_DOWN:
                    y1_change = snake_block_size
                    x1_change = 0

        # 更新蛇的位置
        x1 += x1_change
        y1 += y1_change

        # 检查是否撞墙或自撞
        if x1 >= width or x1 < 0 or y1 >= height or y1 < 0 or [x1, y1] in snake_List[:-1]:
            game_close = True
        else:
            snake_Head = [x1, y1]
            snake_List.append(snake_Head)
            if len(snake_List) > Length_of_snake:
                del snake_List[0]

        # 检查是否吃到食物
        if x1 == foodx and y1 == foody:
            foodx = round(random.randrange(0, width - snake_block_size) / 20.0) * 20.0
            foody = round(random.randrange(0, height - snake_block_size) / 20.0) * 20.0
            Length_of_snake += 1

        # 重新绘制窗口
        window.fill(white)
        pygame.draw.rect(window, green, [foodx, foody, snake_block_size, snake_block_size])
        our_snake(snake_block_size, snake_List)
        pygame.display.update()

        clock.tick(snake_speed)

    pygame.quit()
    quit()

gameLoop()
