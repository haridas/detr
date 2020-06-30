python main.py \
    --dataset_file pic2card \
    --test \
    --coco_path /home/haridas/projects/mystique/data/train_and_test-2020-Jun-05-coco \
    --frozen_weights /mnt1/haridas/projects/opensource/detr/outputs-2020-06-30-1593500748/checkpoint.pth \
    --batch_size=2 \
    --num_queries=100 \
    --output_dir /mnt1/haridas/projects/opensource/detr/outputs-2020-06-30-1593500748
