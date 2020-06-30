python main.py --dataset_file pic2card \
    --coco_path /home/haridas/projects/mystique/data/train_and_test-2020-Jun-05-coco \
    --epochs 150 \
    --lr=1e-4 \
    --batch_size=2 \
    --num_queries=100 \
    --output-dir=outputs-`date +%F-%s` \
    --lr_drop 20  \
    --resume=detr-r50_no-class-head.pth
